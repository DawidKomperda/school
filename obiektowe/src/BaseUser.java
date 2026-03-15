import java.util.Scanner;

public abstract class BaseUser {
    private static int idCounter = 1;

    private int id;
    private String username;
    private String password;

    // Default constructor for tests
    public BaseUser() {
        this.id = idCounter++;
    }

    public BaseUser(String username, String password) {
        this.id = idCounter++;
        this.username = username;
        this.password = password;
    }

    public int getId() { return id; }
    public String getUsername() { return username; }
    public void setUsername(String username) { this.username = username; }
    public String getPassword() { return password; }
    public void setPassword(String password) { this.password = password; }

    public boolean login(String inputUsername, String inputPassword) {
        if (this.username != null && this.password != null &&
            this.username.equals(inputUsername) && this.password.equals(inputPassword)) {
            System.out.println(this.username + " successfully logged in.");
            return true;
        }
        System.out.println("Invalid username or password.");
        return false;
    }

    public abstract String getRoleName();
    public abstract boolean canApproveOrders();
    protected abstract int getSecurityClearance();

    public BaseUser createUser(BaseUser newUser) {
        // Validate if 'this' user has permission to introduce 'newUser' into the system
        if (this.getSecurityClearance() >= 50 && this.getSecurityClearance() >= newUser.getSecurityClearance()) {
            System.out.println(this.getRoleName() + " successfully created/validated " + newUser.getRoleName());
            // In a real system, you would save 'newUser' to a database or user list here.
            return newUser;
        } else {
            throw new SecurityException(this.getRoleName() + " cannot create " + newUser.getRoleName());
        }
    }

    public boolean deleteUser(BaseUser userToDelete) {
        if (this.getSecurityClearance() >= 50 && this.getSecurityClearance() >= userToDelete.getSecurityClearance()) {
            System.out.println("User " + userToDelete.getUsername() + " successfully deleted by " + this.getUsername() + " (" + this.getRoleName() + ")");
            return true;
        } else {
            System.out.println(this.getRoleName() + " does not have permission to delete " + userToDelete.getRoleName());
            throw new SecurityException("Permission denied to delete user.");
        }
    }

    public void displayStock(Storage storage) {
        System.out.println("--- Products in Storage ---");
        for (Items item : storage.getProductNames()) {
            System.out.println("ID: " + item.getId() + " | Name: " + item.getProductName() + " | Amount: " + item.getNumber());
        }
        System.out.println("---------------------------");
    }

    public void itemSell(int itemId, int quantity, Storage storage) {
        Items item = storage.findItemById(itemId);
        if (item != null) {
            if (item.getNumber() >= quantity) {
                storage.decreaseStockById(itemId, quantity);
                System.out.println("Sold " + quantity + "x " + item.getProductName());
            } else {
                System.out.println("Not enough items in stock to sell.");
            }
        } else {
            System.out.println("Item ID " + itemId + " not found.");
        }
    }

    public void itemReturn(int itemId, int quantity, Storage storage) {
        Items item = storage.findItemById(itemId);
        if (item != null) {
            storage.increaseStockById(itemId, quantity);
            System.out.println("Returned " + quantity + "x " + item.getProductName() + " to storage!");
        } else {
            System.out.println("Item ID " + itemId + " not found in storage.");
        }
    }
}
