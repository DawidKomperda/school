library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity vending_machine is
    Port ( 
        clk : in STD_LOGIC;
        reset : in STD_LOGIC;
        
        -- Inputs
        product_select : in STD_LOGIC_VECTOR(2 downto 0); -- 000: Brak, 001: Sok, 010: Cola, 011: Pepsi, 100: Woda
        payment_method : in STD_LOGIC_VECTOR(1 downto 0); -- 00: Gotówka, 01: Karta, 10: Blik
        payment_amount : in INTEGER range 0 to 100; -- Wprowadzona kwota (dla gotówki)
        payment_valid : in STD_LOGIC; -- Sygnał potwierdzenia Karty/Blika
        payment_rejected : in STD_LOGIC; -- Sygnał odrzucenia Karty/Blika
        
        -- Outputs
        dispense_product : out STD_LOGIC;
        dispense_change : out STD_LOGIC;
        out_of_stock : out STD_LOGIC;
        payment_error : out STD_LOGIC;
        change_amount : out INTEGER range 0 to 100;
        -- Wyjścia monet (Wartości: 5.00, 2.00, 1.00, 0.50, 0.20, 0.10)
        coin_5 : out INTEGER range 0 to 10;
        coin_2 : out INTEGER range 0 to 10;
        coin_1 : out INTEGER range 0 to 10;
        coin_0_50 : out INTEGER range 0 to 10;
        coin_0_20 : out INTEGER range 0 to 10;
        coin_0_10 : out INTEGER range 0 to 10;
        
        current_state_out : out STD_LOGIC_VECTOR(2 downto 0) -- Do debugowania
    );
end vending_machine;

architecture Behavioral of vending_machine is

    -- Definicja stanów
    type state_type is (IDLE, CHECK_SELECTION, WAIT_PAYMENT, DISPENSE_ITEM, CALC_CHANGE, GIVE_CHANGE);
    signal current_state : state_type;
    
    -- Sygnały wewnętrzne
    signal price : INTEGER range 0 to 100 := 0;
    signal amount_paid : INTEGER range 0 to 100 := 0;
    signal change_due : INTEGER range 0 to 100 := 0;
    
    -- System magazynowy
    type inventory_type is array (1 to 4) of INTEGER range 0 to 10;
    signal stock : inventory_type := (others => 5); -- Start z 5 sztukami każdego produktu
    signal selected_idx : INTEGER range 0 to 4 := 1;
    
    -- Magazyn monet (Liczba dostępnych monet)
    signal stock_coin_5 : INTEGER range 0 to 50 := 20;
    signal stock_coin_2 : INTEGER range 0 to 50 := 20;
    signal stock_coin_1 : INTEGER range 0 to 50 := 20;
    signal stock_coin_0_50 : INTEGER range 0 to 50 := 20;
    signal stock_coin_0_20 : INTEGER range 0 to 50 := 20;
    signal stock_coin_0_10 : INTEGER range 0 to 50 := 20;

    -- Ceny produktów przechowywane w tablicy dla łatwiejszego dostępu
    -- Indeks: 1=Sok, 2=Cola, 3=Pepsi, 4=Woda
    type price_array_type is array (1 to 4) of INTEGER range 0 to 100;
    constant PRODUCT_PRICES : price_array_type := (20, 30, 30, 15);

begin

    -- Główny Proces
    process(clk, reset)
        variable temp_change : INTEGER range 0 to 100;
        variable num_coins : INTEGER range 0 to 100;
    begin
        if reset = '1' then
            current_state <= IDLE;
            stock <= (others => 5);
            
            -- Reset stanu monet
            stock_coin_5 <= 20;
            stock_coin_2 <= 20;
            stock_coin_1 <= 20;
            stock_coin_0_50 <= 20;
            stock_coin_0_20 <= 20;
            stock_coin_0_10 <= 20;
            
            dispense_product <= '0';
            dispense_change <= '0';
            out_of_stock <= '0';
            payment_error <= '0';
            change_amount <= 0;
            
            coin_5 <= 0;
            coin_2 <= 0;
            coin_1 <= 0;
            coin_0_50 <= 0;
            coin_0_20 <= 0;
            coin_0_10 <= 0;
            
            price <= 0;
            amount_paid <= 0;
            change_due <= 0;
            selected_idx <= 1; -- Inicjalizacja na poprawny indeks
            current_state_out <= "000";
            
        elsif rising_edge(clk) then
            -- Domyślne wartości wyjść
            dispense_product <= '0';
            dispense_change <= '0';
            out_of_stock <= '0';
            payment_error <= '0';
            
            -- Reset wyjść monet, gdy nie wydajemy reszty
            if current_state /= GIVE_CHANGE then
                coin_5 <= 0;
                coin_2 <= 0;
                coin_1 <= 0;
                coin_0_50 <= 0;
                coin_0_20 <= 0;
                coin_0_10 <= 0;
            end if;
            
            case current_state is
                when IDLE =>
                    -- Stan Czuwania: Automat czeka na wybór produktu przez użytkownika.
                    current_state_out <= "000";
                    if product_select /= "000" then
                        current_state <= CHECK_SELECTION;
                    end if;
                    
                when CHECK_SELECTION =>
                    -- Stan Sprawdzania Wyboru: Sprawdza czy produkt istnieje i czy jest dostępny w magazynie.
                    current_state_out <= "001";
                    
                    -- Zoptymalizowana logika wyboru przy użyciu tablicy
                    -- Konwersja "001" -> 1, "010" -> 2, itd.
                    if unsigned(product_select) >= 1 and unsigned(product_select) <= 4 then
                        -- Sprawdź czy produkt jest w magazynie
                        if stock(to_integer(unsigned(product_select))) > 0 then
                            price <= PRODUCT_PRICES(to_integer(unsigned(product_select)));
                            selected_idx <= to_integer(unsigned(product_select));
                            current_state <= WAIT_PAYMENT;
                        else
                            out_of_stock <= '1';
                            current_state <= IDLE;
                        end if;
                    else
                        current_state <= IDLE; -- Nieprawidłowy wybór
                    end if;
                    
                when WAIT_PAYMENT =>
                    -- Stan Oczekiwania na Płatność: Czeka na wpłatę.
                    -- Dla gotówki sprawdza kwotę. Dla karty/blika czeka na potwierdzenie.
                    current_state_out <= "010";
                    
                    if payment_method = "00" then -- Gotówka
                        if payment_amount >= price then
                            amount_paid <= payment_amount;
                            current_state <= DISPENSE_ITEM;
                        end if;
                    elsif payment_method = "01" or payment_method = "10" then -- Karta lub Blik
                        -- Sprawdź czy płatność jest ważna ORAZ kwota jest wystarczająca
                        if payment_valid = '1' and payment_amount >= price then
                            current_state <= DISPENSE_ITEM;
                        elsif payment_rejected = '1' then
                            payment_error <= '1'; -- Wyświetl komunikat "0" (Błąd)
                            current_state <= IDLE;
                        end if;
                    end if;
                    
                when DISPENSE_ITEM =>
                    -- Stan Wydawania Produktu: Wydaje produkt i zmniejsza stan magazynowy.
                    current_state_out <= "011";
                    dispense_product <= '1';
                    
                    -- Zmniejsz stan magazynowy
                    if selected_idx > 0 then
                        stock(selected_idx) <= stock(selected_idx) - 1;
                    end if;
                    
                    if payment_method = "00" then -- Gotówka
                        current_state <= CALC_CHANGE;
                    else -- Karta lub Blik
                        current_state <= IDLE;
                    end if;
                    
                when CALC_CHANGE =>
                    -- Stan Obliczania Reszty: Oblicza ile reszty trzeba oddać.
                    current_state_out <= "100";
                    change_due <= amount_paid - price;
                    if (amount_paid - price) > 0 then
                        current_state <= GIVE_CHANGE;
                    else
                        current_state <= IDLE;
                    end if;
                    
                when GIVE_CHANGE =>
                    -- Stan Wydawania Reszty: Algorytm zachłanny.
                    -- Wydaje resztę używając dostępnych monet od największej do najmniejszej.
                    current_state_out <= "101";
                    dispense_change <= '1';
                    change_amount <= change_due;
                    
                    -- Oblicz monety zaczynając od największej (5.00 = 50 jednostek)
                    -- Sprawdź dostępność w magazynie
                    temp_change := change_due;
                    
                    -- Monety 5.00
                    num_coins := temp_change / 50;
                    if num_coins > stock_coin_5 then
                        num_coins := stock_coin_5;
                    end if;
                    coin_5 <= num_coins;
                    stock_coin_5 <= stock_coin_5 - num_coins;
                    temp_change := temp_change - (num_coins * 50);
                    
                    -- Monety 2.00
                    num_coins := temp_change / 20;
                    if num_coins > stock_coin_2 then
                        num_coins := stock_coin_2;
                    end if;
                    coin_2 <= num_coins;
                    stock_coin_2 <= stock_coin_2 - num_coins;
                    temp_change := temp_change - (num_coins * 20);
                    
                    -- Monety 1.00
                    num_coins := temp_change / 10;
                    if num_coins > stock_coin_1 then
                        num_coins := stock_coin_1;
                    end if;
                    coin_1 <= num_coins;
                    stock_coin_1 <= stock_coin_1 - num_coins;
                    temp_change := temp_change - (num_coins * 10);
                    
                    -- Monety 0.50
                    num_coins := temp_change / 5;
                    if num_coins > stock_coin_0_50 then
                        num_coins := stock_coin_0_50;
                    end if;
                    coin_0_50 <= num_coins;
                    stock_coin_0_50 <= stock_coin_0_50 - num_coins;
                    temp_change := temp_change - (num_coins * 5);
                    
                    -- Monety 0.20
                    num_coins := temp_change / 2;
                    if num_coins > stock_coin_0_20 then
                        num_coins := stock_coin_0_20;
                    end if;
                    coin_0_20 <= num_coins;
                    stock_coin_0_20 <= stock_coin_0_20 - num_coins;
                    temp_change := temp_change - (num_coins * 2);
                    
                    -- Monety 0.10
                    num_coins := temp_change;
                    if num_coins > stock_coin_0_10 then
                        num_coins := stock_coin_0_10;
                    end if;
                    coin_0_10 <= num_coins;
                    stock_coin_0_10 <= stock_coin_0_10 - num_coins;
                    
                    current_state <= IDLE;
                    
                when others =>
                    current_state <= IDLE;
            end case;
        end if;
    end process;

end Behavioral;
