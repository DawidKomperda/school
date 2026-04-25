import java.util.Scanner;

public abstract class BaseUser {
    private static int idCounter = 1;

    private int id;
    private String username;
    private String password;


    public BaseUser() {
        this.id = idCounter++;
    }

    public BaseUser(String username, String password) {
        this.id = idCounter++;
        this.username = username;
        this.password = password;
    }

    public static void decrementIdCounter() {
        if (idCounter > 1) {
            idCounter--;
        }
    }

    public int getId() { return id; }
    public String getUsername() { return username; }
    public void setUsername(String username) { this.username = username; }
    public String getPassword() { return password; }
    public void setPassword(String password) { this.password = password; }

    public boolean login(String inputUsername, String inputPassword) {
        if (this.username != null && this.password != null &&
            this.username.equals(inputUsername) && this.password.equals(inputPassword)) {
            return true;
        }
        return false;
    }

    public abstract String getRoleName();
    public abstract boolean canApproveOrders();
    protected abstract int getSecurityClearance();

    public BaseUser createUser(BaseUser newUser) {

        if (this.getSecurityClearance() >= 50 && this.getSecurityClearance() >= newUser.getSecurityClearance()) {
            System.out.println(this.getRoleName() + " successfully created/validated " + newUser.getRoleName());

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

    public boolean changeUserPassword(BaseUser targetUser, String newPassword) {
        if (this.getSecurityClearance() >= 100) {
            targetUser.setPassword(newPassword);
            System.out.println("Password for user " + targetUser.getUsername() + " successfully changed by " + this.getUsername() + ".");
            return true;
        } else {
            System.out.println(this.getRoleName() + " does not have permission to change user passwords.");
            throw new SecurityException("Permission denied to change password.");
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
