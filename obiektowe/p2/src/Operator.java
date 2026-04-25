import java.time.LocalDateTime;

public class Operator {
    protected final Database db;

    public Operator(Database db) {
        this.db = db;
    }

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

    public void estimateCompletion(int orderId, LocalDateTime estimatedTime) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getState() == OrderState.STARTED || order.getState() == OrderState.DELAYED) {
                order.setTime3EstimatedCompletion(estimatedTime);
                db.updateOrder(order);
            }
        });
    }

    public void markAsDelayed(int orderId) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getState() != OrderState.COMPLETED) {
                order.setState(OrderState.DELAYED);
                db.updateOrder(order);
            }
        });
    }

    public void editOperatorComment(int orderId, String newComment) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getState() != OrderState.COMPLETED) {
                order.setOperatorComment(newComment);
                db.updateOrder(order);
            }
        });
    }

    public void completeOrder(int orderId) {
        db.getOrderById(orderId).ifPresent(order -> {
            order.setState(OrderState.COMPLETED);
            db.updateOrder(order);
        });
    }
}
