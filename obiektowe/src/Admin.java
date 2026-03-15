public class Admin extends BaseUser implements WareManager {

    public Admin() {
        super();
    }

    public Admin(String username, String password) {
        super(username, password);
    }

    @Override
    public String getRoleName() { return "Admin"; }

    @Override
    public boolean canApproveOrders() { return true; }

    @Override
    protected int getSecurityClearance() { return 100; }
    
    public void changePassword(BaseUser targetUser, String newPassword) {
        targetUser.setPassword(newPassword);
        System.out.println("Password changed for user " + targetUser.getUsername());
    }
}
