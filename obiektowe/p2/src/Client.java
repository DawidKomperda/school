public class Client {
    private final String firstName;
    private final String lastName;
    private final Database db;

    public Client(String firstName, String lastName, Database db) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.db = db;
    }

    public Order createOrder(String comment) {
        return db.addOrder(firstName, lastName, comment);
    }

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
