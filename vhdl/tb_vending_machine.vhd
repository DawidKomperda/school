library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_vending_machine is
end tb_vending_machine;

architecture Behavioral of tb_vending_machine is

    component vending_machine
        Port ( 
            clk : in STD_LOGIC;
            reset : in STD_LOGIC;
            product_select : in STD_LOGIC_VECTOR(2 downto 0);
            payment_method : in STD_LOGIC_VECTOR(1 downto 0);
            payment_amount : in INTEGER range 0 to 100;
            payment_valid : in STD_LOGIC;
            payment_rejected : in STD_LOGIC;
            dispense_product : out STD_LOGIC;
            dispense_change : out STD_LOGIC;
            out_of_stock : out STD_LOGIC;
            payment_error : out STD_LOGIC;
            change_amount : out INTEGER range 0 to 100;
            coin_5 : out INTEGER range 0 to 10;
            coin_2 : out INTEGER range 0 to 10;
            coin_1 : out INTEGER range 0 to 10;
            coin_0_50 : out INTEGER range 0 to 10;
            coin_0_20 : out INTEGER range 0 to 10;
            coin_0_10 : out INTEGER range 0 to 10;
            -- Added Alert Outputs
            owner_alert_stock : out STD_LOGIC;
            owner_alert_coins : out STD_LOGIC;
            current_state_out : out STD_LOGIC_VECTOR(2 downto 0)
        );
    end component;

    -- Inputs
    signal clk : STD_LOGIC := '0';
    signal reset : STD_LOGIC := '0';
    signal product_select : STD_LOGIC_VECTOR(2 downto 0) := "000";
    signal payment_method : STD_LOGIC_VECTOR(1 downto 0) := "00";
    signal payment_amount : INTEGER range 0 to 100 := 0;
    signal payment_valid : STD_LOGIC := '0';
    signal payment_rejected : STD_LOGIC := '0';

    -- Outputs
    signal dispense_product : STD_LOGIC;
    signal dispense_change : STD_LOGIC;
    signal out_of_stock : STD_LOGIC;
    signal payment_error : STD_LOGIC;
    signal change_amount : INTEGER range 0 to 100;
    signal coin_5, coin_2, coin_1, coin_0_50, coin_0_20, coin_0_10 : INTEGER range 0 to 10;
    -- Added Alert Signals
    signal owner_alert_stock : STD_LOGIC;
    signal owner_alert_coins : STD_LOGIC;
    signal current_state_out : STD_LOGIC_VECTOR(2 downto 0);

    constant clk_period : time := 10 ns;

begin

    uut: vending_machine PORT MAP (
        clk => clk,
        reset => reset,
        product_select => product_select,
        payment_method => payment_method,
        payment_amount => payment_amount,
        payment_valid => payment_valid,
        payment_rejected => payment_rejected,
        dispense_product => dispense_product,
        dispense_change => dispense_change,
        out_of_stock => out_of_stock,
        payment_error => payment_error,
        change_amount => change_amount,
        coin_5 => coin_5,
        coin_2 => coin_2,
        coin_1 => coin_1,
        coin_0_50 => coin_0_50,
        coin_0_20 => coin_0_20,
        coin_0_10 => coin_0_10,
        owner_alert_stock => owner_alert_stock,
        owner_alert_coins => owner_alert_coins,
        current_state_out => current_state_out
    );

    clk_process :process
    begin
        clk <= '0';
        wait for clk_period/2;
        clk <= '1';
        wait for clk_period/2;
    end process;

    stim_proc: process
    begin		
        reset <= '1';
        wait for 100 ns;	
        reset <= '0';
        wait for clk_period*10;

        -- Przypadek testowy 1: Sok jabłkowy za Gotówkę
        product_select <= "001";
        wait for clk_period;
        payment_method <= "00";
        payment_amount <= 25;
        wait for clk_period*5;
        product_select <= "000";
        payment_amount <= 0;
        wait for clk_period*10;
        
        -- Przypadek testowy 2: Cola Kartą
        product_select <= "010";
        wait for clk_period;
        payment_method <= "01";
        payment_amount <= 30;
        payment_valid <= '1';
        wait for clk_period*5;
        product_select <= "000";
        payment_amount <= 0;
        payment_valid <= '0';
        wait for clk_period*10;

        -- Przypadek testowy 3: Pepsi Blikiem
        product_select <= "011";
        wait for clk_period;
        payment_method <= "10";
        payment_amount <= 30;
        payment_valid <= '1';
        wait for clk_period*5;
        product_select <= "000";
        payment_amount <= 0;
        payment_valid <= '0';
        wait for clk_period*10;

        wait;
    end process;

end Behavioral;
