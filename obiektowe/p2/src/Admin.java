public class Admin extends Operator {

    public Admin(Database db) {
        super(db);
    }

    public void deleteOrder(int orderId) {
        db.getOrderById(orderId).ifPresent(order -> {
            if (order.getState() != OrderState.COMPLETED) {
                db.removeOrder(order);
            }
        });
    }

    public void removeClient(String firstName, String lastName) {
        db.deleteClientData(firstName, lastName);
    }
}
