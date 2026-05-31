import java.time.LocalDateTime;

/**
 * Model encji Zlecenia. Zlecenie to główne obiekty przepływowe w programie.
 * Poszczególne operacje pozwalają na zmianę stanu `state`, np. Started (przez Operatora), Delayed i Finalized.
 * Posiada ślad wprowadzanych komentarzy (klienckie i operacyjne) ułatwiając logikę komunikacji w bilecie.
 */
public class Order {
    private final int id;
    private final String clientFirstName;
    private final String clientLastName;
    
    private String clientComment;
    private String operatorComment;
    
    private final LocalDateTime time1Creation;
    private LocalDateTime time2Start;
    private LocalDateTime time3EstimatedCompletion;
    
    private OrderState state;

    /**
     * Konstruktor Order. Inicjalizuje wszystkie pola niezbędne dla nowego zlecenia.
     * Stan początkowy zawsze to NOT_STARTED.
     * 
     * @param id Unikalny identyfikator zlecenia (auto-generated)
     * @param clientFirstName Imię klienta
     * @param clientLastName Nazwisko klienta
     * @param clientComment Początkowy komentarz/opis od klienta
     * @param time1Creation Czas utworzenia zlecenia
     */
    public Order(int id, String clientFirstName, String clientLastName, String clientComment, LocalDateTime time1Creation) {
        this.id = id;
        this.clientFirstName = clientFirstName;
        this.clientLastName = clientLastName;
        this.clientComment = clientComment;
        this.time1Creation = time1Creation;
        this.state = OrderState.NOT_STARTED;
    }

    // ===== Gettery i Settery =====
    
    /**
     * Getter na niezmienialny ID zlecenia.
     */
    public int getId() { return id; }
    
    /**
     * Getter na imię klienta (niezmienne).
     */
    public String getClientFirstName() { return clientFirstName; }
    
    /**
     * Getter na nazwisko klienta (niezmienne).
     */
    public String getClientLastName() { return clientLastName; }
    
    /**
     * Getter na komentarz klienta - może być modyfikowany przez klienta.
     */
    public String getClientComment() { return clientComment; }
    
    /**
     * Setter na komentarz klienta.
     * Klient może edytować własny komentarz do czasu aż zlecenie nie będzie COMPLETED.
     */
    public void setClientComment(String clientComment) { this.clientComment = clientComment; }
    
    /**
     * Getter na komentarz operatora - dodawany przez operatora podczas przetwarzania.
     */
    public String getOperatorComment() { return operatorComment; }
    
    /**
     * Setter na komentarz operatora zawierający notatki techniczne/diagnostyczne.
     */
    public void setOperatorComment(String operatorComment) { this.operatorComment = operatorComment; }

    /**
     * Getter na czas utworzenia zlecenia (niezmienne).
     */
    public LocalDateTime getTime1Creation() { return time1Creation; }
    
    /**
     * Getter na czas rozpoczęcia pracy przez operatora.
     * Null dopóki stan nie zmieni się na STARTED.
     */
    public LocalDateTime getTime2Start() { return time2Start; }
    
    /**
     * Setter na czas rozpoczęcia - ustawiany gdy operator przepisuje zlecenie.
     */
    public void setTime2Start(LocalDateTime time2Start) { this.time2Start = time2Start; }
    
    /**
     * Getter na szacunkowy czas zakończenia pracy.
     * Null do momentu gdy operator przypisze estymatę.
     */
    public LocalDateTime getTime3EstimatedCompletion() { return time3EstimatedCompletion; }
    
    /**
     * Setter na szacunkowy czas ukończenia zlecenia.
     */
    public void setTime3EstimatedCompletion(LocalDateTime time3EstimatedCompletion) { this.time3EstimatedCompletion = time3EstimatedCompletion; }

    /**
     * Getter na obecny stan zlecenia (NOT_STARTED, STARTED, DELAYED, COMPLETED).
     */
    public OrderState getState() { return state; }
    
    /**
     * Setter na stan zlecenia. Zmiany stanu przechodzą przez walidacje w logice Role.
     */
    public void setState(OrderState state) { this.state = state; }
}
