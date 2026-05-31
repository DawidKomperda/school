/**
 * Klasa Klienta, tworzona po podaniu imienia i nazwiska w systemie powłoki.
 * Działa jako reprezentant zgłaszającego zlecenie. Posiada metody umożliwiające 
 * bezpośrednie utworzenie nowych biletów zgłoszeniowych (Order) i modyfikację komentarza.
 */
public class Client {
    private final String firstName;
    private final String lastName;
    private final Database db;

    /**
     * Konstruktor Client. Inicjalizuje klienta na podstawie podanego imienia i nazwiska.
     * Otrzymuje referencję do bazy danych do wykonywania operacji.
     * 
     * @param firstName Imię klienta
     * @param lastName Nazwisko klienta
     * @param db Instancja bazy danych (Singleton)
     */
    public Client(String firstName, String lastName, Database db) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.db = db;
    }

    /**
     * Tworzy nowe zlecenie w imieniu zalogowanego klienta.
     * Zwraca nowy Order z unikalnym ID, przypisanym do tego klienta.
     * Stan początkowy: NOT_STARTED.
     * 
     * @param comment Opisowy komentarz/życzenie od klienta
     * @return Nowo utworzony Order
     */
    public Order createOrder(String comment) {
        return db.addOrder(firstName, lastName, comment);
    }

    /**
     * Edytuje komentarz do własnego zlecenia.
     * Klient może edytować swój komentarz tylko jeśli:
     * - Zlecenie należy do tego klienta (po imienia i nazwisku)
     * - Zlecenie nie jest jeszcze w stanie COMPLETED
     * 
     * @param orderId ID zlecenia do edycji
     * @param newComment Nowy tekst komentarza
     */
    public void editOrderComment(int orderId, String newComment) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getClientFirstName().equals(firstName) && 
                order.getClientLastName().equals(lastName) && 
                order.getState() != OrderState.COMPLETED) {
                order.setClientComment(newComment);
                db.updateOrder(order);
            }
        });
    }

    /**
     * Oznacza własne zlecenie jako opóźnione (DELAYED).
     * Klient może zmienić stan tylko swoich zleceń które nie są COMPLETED.
     * 
     * @param orderId ID zlecenia do opóźnienia
     */
    public void delayOrder(int orderId) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getClientFirstName().equals(firstName) && 
                order.getClientLastName().equals(lastName) &&
                order.getState() != OrderState.COMPLETED) {
                order.setState(OrderState.DELAYED);
                db.updateOrder(order);
            }
        });
    }
}
