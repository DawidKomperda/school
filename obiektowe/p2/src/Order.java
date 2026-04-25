import java.time.LocalDateTime;

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

    public Order(int id, String clientFirstName, String clientLastName, String clientComment, LocalDateTime time1Creation) {
        this.id = id;
        this.clientFirstName = clientFirstName;
        this.clientLastName = clientLastName;
        this.clientComment = clientComment;
        this.time1Creation = time1Creation;
        this.state = OrderState.NOT_STARTED;
    }

    public int getId() { return id; }
    public String getClientFirstName() { return clientFirstName; }
    public String getClientLastName() { return clientLastName; }
    public String getClientComment() { return clientComment; }
    public void setClientComment(String clientComment) { this.clientComment = clientComment; }
    
    public String getOperatorComment() { return operatorComment; }
    public void setOperatorComment(String operatorComment) { this.operatorComment = operatorComment; }

    public LocalDateTime getTime1Creation() { return time1Creation; }
    
    public LocalDateTime getTime2Start() { return time2Start; }
    public void setTime2Start(LocalDateTime time2Start) { this.time2Start = time2Start; }
    
    public LocalDateTime getTime3EstimatedCompletion() { return time3EstimatedCompletion; }
    public void setTime3EstimatedCompletion(LocalDateTime time3EstimatedCompletion) { this.time3EstimatedCompletion = time3EstimatedCompletion; }

    public OrderState getState() { return state; }
    public void setState(OrderState state) { this.state = state; }
}
