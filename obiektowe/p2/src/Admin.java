/**
 * Klasa Administratora dziedzicząca możliwości i zachowania Operatora.
 * Jako rzadkie uprawnienie, Administrator ma też niszczącą moc kasowania zleceń z systemu pomimo 
 * zasad walidacji, pozwalając na swobodne usuwanie obiektów i klientów.
 */
public class Admin extends Operator {

    /**
     * Konstruktor Admin. Inicjalizuje administratora z referencją do bazy danych.
     * Admin dziedziczy po Operator, więc ma dostęp do wszystkich metod operatora.
     * 
     * @param db Instancja bazy danych (Singleton)
     */
    public Admin(Database db) {
        super(db);
    }

    /**
     * Usuwa zlecenie z systemu (uprawnienie administratora).
     * Może usunąć tylko zlecenia które nie są w stanie COMPLETED.
     * Po usunięciu dane zlecenia są permanentnie usunięte z bazy.
     * 
     * @param orderId ID zlecenia do usunięcia
     */
    public void deleteOrder(int orderId) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getState() != OrderState.COMPLETED) {
                db.removeOrder(order);
            }
        });
    }

    /**
     * Usuwa wszystkie niezakończone zlecenia danego klienta.
     * Administrator może wyczystować wszystkie dane klienta (oprócz zleceń COMPLETED).
     * Wykorzystywane gdy np. klient rezygnuje z usług lub zażąda usunięcia danych.
     * 
     * @param firstName Imię klienta
     * @param lastName Nazwisko klienta
     */
    public void removeClient(String firstName, String lastName) {
        db.deleteClientData(firstName, lastName);
    }
}
