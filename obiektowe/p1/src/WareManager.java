import java.util.Scanner;

public interface WareManager {
    default void manageWares(Storage storage) {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter Item ID to edit: ");
        int itemId = Integer.parseInt(in.nextLine());
        
        Items item = storage.findItemById(itemId);
        if (item == null) {
            System.out.println("Item not found.");
            return;
        }
        
        System.out.println("Editing: " + item.getProductName() + " (Amount: " + item.getNumber() + ")");
        System.out.println("1. Change Name");
        System.out.println("2. Change Stock Number");
        System.out.print("Choice: ");
        String choice = in.nextLine();
        
        String newName = item.getProductName();
        int newAmount = item.getNumber();

        if (choice.equals("1")) {
            System.out.print("New Name: ");
            newName = in.nextLine();
        } else if (choice.equals("2")) {
            System.out.print("New Stock Amount: ");
            newAmount = Integer.parseInt(in.nextLine());
        } else {
            System.out.println("Invalid choice.");
            return;
        }
        
        editStorageDetail(storage, itemId, newName, newAmount);
    }

    default void editStorageDetail(Storage storage, int itemId, String newName, int newAmount) {
        Items item = storage.findItemById(itemId);
        if (item != null) {
            item.setProductName(newName);
            item.setNumber(newAmount);
            System.out.println("Item ID: " + itemId + " successfully updated!");
        } else {
            System.out.println("Item not found. Could not edit.");
        }
    }
}
