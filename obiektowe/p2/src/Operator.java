import java.time.LocalDateTime;

/**
 * Klasa Operator w systemie. Posiada kluczowe zadania przetwarzania 
 * spływających zgłoszeń od Klientów, przydzielania orientacyjnych estymat czasowych 
 * dla rozwiązania ich problemów czy modyfikacji komentarza specjalistycznego.
 */
public class Operator {
    protected final Database db;

    /**
     * Konstruktor Operator. Inicjalizuje operatora z referencją do bazy danych.
     * 
     * @param db Instancja bazy danych (Singleton)
     */
    public Operator(Database db) {
        this.db = db;
    }

    /**
     * Przejmuje nowe zlecenie do przetwarzania.
     * Zmienia stan z NOT_STARTED na STARTED i ustawia:
     * - Komentarz operatora z diagnozą
     * - Czas rozpoczęcia (time2Start) na obecny czas
     * Operacja jest atomikiem - jeśli stan nie jest NOT_STARTED, nic się nie zmienia.
     * 
     * @param orderId ID zlecenia do przetworzenia
     * @param operatorComment Komentarz diagnostyczny operatora
     */
    public void processNewOrder(int orderId, String operatorComment) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getState() == OrderState.NOT_STARTED) {
                order.setOperatorComment(operatorComment);
                order.setState(OrderState.STARTED);
                order.setTime2Start(LocalDateTime.now());
                db.updateOrder(order);
            }
        });
    }

    /**
     * Ustawia szacunkowy czas ukończenia zlecenia.
     * Operator podaje przyszły czas (LocalDateTime) kiedy będzie gotowy.
     * Operacja jest dostępna tylko gdy stan to STARTED lub DELAYED.
     * 
     * @param orderId ID zlecenia
     * @param estimatedTime Przyszły czas zakończenia (LocalDateTime)
     */
    public void estimateCompletion(int orderId, LocalDateTime estimatedTime) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getState() == OrderState.STARTED || order.getState() == OrderState.DELAYED) {
                order.setTime3EstimatedCompletion(estimatedTime);
                db.updateOrder(order);
            }
        });
    }

    /**
     * Oznacza zlecenie jako opóźnione (DELAYED).
     * Operacja dostępna dla zleceń które nie są COMPLETED.
     * Operator może zmienić stan na DELAYED z dowolnego stanu (oprócz COMPLETED).
     * 
     * @param orderId ID zlecenia do opóźnienia
     */
    public void markAsDelayed(int orderId) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getState() != OrderState.COMPLETED) {
                order.setState(OrderState.DELAYED);
                db.updateOrder(order);
            }
        });
    }

    /**
     * Edytuje komentarz operatora dla dowolnego zlecenia.
     * Może modyfikować swoje notatki diagnostyczne dopóki zlecenie nie jest COMPLETED.
     * 
     * @param orderId ID zlecenia
     * @param newComment Nowy komentarz operatora
     */
    public void editOperatorComment(int orderId, String newComment) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getState() != OrderState.COMPLETED) {
                order.setOperatorComment(newComment);
                db.updateOrder(order);
            }
        });
    }

    /**
     * Oznacza zlecenie jako ukończone (COMPLETED).
     * Po tej operacji zlecenie jest zamknięte i nikomu nie wolno go już zmieniać.
     * 
     * @param orderId ID zlecenia do zamknięcia
     */
    public void completeOrder(int orderId) {
        db.getOrderById(orderId).ifPresent(order -> {
            order.setState(OrderState.COMPLETED);
            db.updateOrder(order);
        });
    }
}
