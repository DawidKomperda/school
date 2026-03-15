public class Employee extends BaseUser {

    public Employee() {
        super();
    }

    public Employee(String username, String password) {
        super(username, password);
    }

    @Override
    public String getRoleName() { return "Employee"; }

    @Override
    public boolean canApproveOrders() { return false; }

    @Override
    protected int getSecurityClearance() { return 10; }
}
