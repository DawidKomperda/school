public class Manager extends BaseUser implements WareManager {

    public Manager() {
        super();
    }

    public Manager(String username, String password) {
        super(username, password);
    }
    
    @Override
    public String getRoleName() { return "Manager"; }
    
    @Override
    public boolean canApproveOrders() { return true; }
    
    @Override
    protected int getSecurityClearance() { return 50; }
}
