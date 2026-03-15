import java.util.ArrayList;
import java.util.List;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    private static List<BaseUser> users = new ArrayList<>();
    private static BaseUser currentUser = null;
    private static Storage storage = new Storage();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Pre-create some base data
        Admin initialAdmin = new Admin();
        initialAdmin.setUsername("admin");
        initialAdmin.setPassword("admin123");
        users.add(initialAdmin);
        
        for (int i = 1; i <= 2; i++) {
            Manager m = new Manager();
            m.setUsername("manager" + i);
            m.setPassword("pass");
            users.add(m);
        }
        
        for (int i = 1; i <= 4; i++) {
            Employee e = new Employee();
            e.setUsername("employee" + i);
            e.setPassword("pass");
            users.add(e);
        }
        
        String[] sampleItems = {"Apple", "Banana", "Milk", "Bread", "Water", "Eggs", "Cheese", "Butter", "Chicken", "Rice"};
        for (String itemName : sampleItems) {
            Items item = new Items();
            item.setId(storage.getNextAvailableId());
            item.setProductName(itemName);
            item.setNumber(50); // initial stock
            storage.addItem(item);
        }
        
        while (true) {
            System.out.println("\n=== Warehouse Management System ===");
            if (currentUser == null) {
                System.out.println("1. Login");
                System.out.println("0. Exit");
                System.out.print("Choose option: ");
                
                String choice = scanner.nextLine();
                if (choice.equals("1")) {
                    handleLogin();
                } else if (choice.equals("0")) {
                    break;
                } else {
                    System.out.println("Invalid option.");
                }
            } else {
                System.out.println("Logged in as: " + currentUser.getUsername() + " (" + currentUser.getRoleName() + ")");
                System.out.println("1. Logout");
                System.out.println("2. Display Storage");
                if (!(currentUser instanceof Employee)) {
                    System.out.println("3. Manage Users");
                }
                System.out.println("4. Transactions (Sell / Return)");
                System.out.println("5. Manage Orders (Accept new items)");
                if (currentUser instanceof WareManager) {
                    System.out.println("6. Edit Storage Detail (Admin/Manager)");
                }
                
                System.out.print("Choose option: ");
                String choice = scanner.nextLine();
                
                if (choice.equals("1")) {
                    currentUser = null;
                } else if (choice.equals("2")) {
                    currentUser.displayStock(storage);
                } else if (choice.equals("3") && !(currentUser instanceof Employee)) {
                    handleManageUsers();
                } else if (choice.equals("4")) {
                    handleTransactions();
                } else if (choice.equals("5")) {
                    handleOrders();
                } else if (choice.equals("6") && currentUser instanceof WareManager) {
                    System.out.println("--- Current Storage ---");
                    currentUser.displayStock(storage);
                    ((WareManager) currentUser).manageWares(storage);
                } else {
                    System.out.println("Invalid option.");
                }
            }
        }
    }
    
    private static void handleLogin() {
        System.out.print("Username: ");
        String uname = scanner.nextLine();
        System.out.print("Password: ");
        String pwd = scanner.nextLine();
        
        for (BaseUser u : users) {
            if (u.login(uname, pwd)) {
                currentUser = u;
                return;
            }
        }
    }
    
    private static void handleManageUsers() {
        System.out.println("--- Manage Users ---");
        System.out.println("Total Users: " + users.size());
        for (BaseUser u : users) {
            System.out.println("ID: " + u.getId() + " | Name: " + (u.getUsername() == null ? "N/A" : u.getUsername()) + " | Role: " + u.getRoleName());
        }
        System.out.println("1. Create User");
        System.out.println("2. Delete User");
        System.out.println("0. Back");
        System.out.print("Choice: ");
        String c = scanner.nextLine();

        if (c.equals("1")) {
            System.out.println("Select role to create: 1. Admin  2. Manager  3. Employee");
            String r = scanner.nextLine();
            BaseUser newUser = null;
            if (r.equals("1")) newUser = new Admin();
            else if (r.equals("2")) newUser = new Manager();
            else if (r.equals("3")) newUser = new Employee();
            else {
                System.out.println("Invalid role.");
                return;
            }
            
            System.out.print("Set username: ");
            newUser.setUsername(scanner.nextLine());
            System.out.print("Set password: ");
            newUser.setPassword(scanner.nextLine());
            
            try {
                currentUser.createUser(newUser);
                users.add(newUser);
                System.out.println("User added to system list.");
            } catch (SecurityException e) {
                System.out.println("Error: " + e.getMessage());
            }
        } else if (c.equals("2")) {
            System.out.print("Enter ID of user to delete: ");
            int idToDelete = Integer.parseInt(scanner.nextLine());
            BaseUser target = null;
            for (BaseUser u : users) {
                if (u.getId() == idToDelete) {
                    target = u;
                    break;
                }
            }
            if (target != null) {
                try {
                    if (currentUser.deleteUser(target)) {
                        users.remove(target);
                        System.out.println("User removed from system list.");
                    }
                } catch (SecurityException e) {
                    // Exception message already handled in BaseUser
                    System.out.println("Delete failed.");
                }
            } else {
                System.out.println("User not found.");
            }
        }
    }
    
    private static void handleTransactions() {
        System.out.println("--- Transactions ---");
        System.out.println("1. Sell Item");
        System.out.println("2. Return Item");
        System.out.print("Choice: ");
        String c = scanner.nextLine();
        
        if (c.equals("1")) {
            currentUser.displayStock(storage);
            try {
                System.out.print("Enter item ID to sell: ");
                int id = Integer.parseInt(scanner.nextLine());
                System.out.print("Enter amount: ");
                int amt = Integer.parseInt(scanner.nextLine());
                currentUser.itemSell(id, amt, storage);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a numerical ID and amount.");
            }
        } else if (c.equals("2")) {
            currentUser.displayStock(storage);
            try {
                System.out.print("Enter item ID to return: ");
                int id = Integer.parseInt(scanner.nextLine());
                System.out.print("Enter amount: ");
                int amt = Integer.parseInt(scanner.nextLine());
                currentUser.itemReturn(id, amt, storage);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a numerical ID and amount.");
            }
        }
    }
    
    private static void handleOrders() {
        System.out.println("--- Manage Orders ---");
        System.out.println("1. Order Accept (Receive new batch into stock)");
        System.out.println("2. Order New (Request items from supplier)");
        System.out.println("3. Order Return (Send items back to supplier)");
        System.out.println("0. Back");
        System.out.print("Choice: ");
        String c = scanner.nextLine();
        
        if (c.equals("0")) return;
        
        BaseOrderWares order = null;
        String arrivedOrderId = null;
        File arrivedFile = null;
        
        try {
            if (c.equals("1")) {
                order = new OrderAccept(currentUser);
                System.out.print("Enter arrived order ID (5-digit number): ");
                arrivedOrderId = scanner.nextLine();
                arrivedFile = new File("orders/arrived/" + arrivedOrderId + ".txt");
                
                if (arrivedFile.exists()) {
                    System.out.println("\n--- Arrived Order Details ---");
                    try (Scanner fileScanner = new Scanner(arrivedFile)) {
                        while (fileScanner.hasNextLine()) {
                            System.out.println(fileScanner.nextLine());
                        }
                    } catch (IOException e) {
                        System.out.println("Could not read arrived file.");
                    }
                    System.out.println("-----------------------------\n");
                } else {
                    System.out.println("Order ID not found in arrived folder.");
                    return;
                }
            } else if (c.equals("2")) {
                order = new OrderNew(currentUser);
            } else if (c.equals("3")) {
                order = new OrderReturn(currentUser);
                System.out.print("Return Reason: ");
                ((OrderReturn) order).setReturnReason(scanner.nextLine());
            } else {
                System.out.println("Invalid option.");
                return;
            }
        } catch (SecurityException e) {
            System.out.println("Permission denied: " + e.getMessage());
            return;
        }

        System.out.print("Supplier: ");
        order.setSupplier(scanner.nextLine());

        if (c.equals("3")) {
            System.out.println("--- Current Storage ---");
            currentUser.displayStock(storage);
        }

        while (true) {
            System.out.print("Enter Item Name (or type 'done' to finish): ");
            String name = scanner.nextLine();
            if (name.equalsIgnoreCase("done")) break;
            
            System.out.print("Amount: ");
            int amount;
            try {
                amount = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                System.out.println("Invalid amount. Please try again.");
                continue;
            }
            
            Items item = new Items();
            item.setProductName(name);
            item.setNumber(amount);
            
            if (order instanceof OrderReturn) {
                Items existing = storage.findItemByName(name);
                if (existing == null) {
                    System.out.println("Error: Item does not exist in storage.");
                    continue;
                }
            } else if (order instanceof OrderNew) {
                Items existing = storage.findItemByName(name);
                if (existing != null) {
                    item.setId(existing.getId());
                    System.out.println("~ Item recognized. Matching existing stock ID: " + item.getId());
                }
            } else {
                Items existing = storage.findItemByName(name);
                if (existing != null) {
                    item.setId(existing.getId());
                    System.out.println("~ Item recognized. Matching existing stock ID: " + item.getId());
                } else {
                    int provisionalId = storage.getNextAvailableId() + order.getItemsList().size();
                    item.setId(provisionalId);
                    System.out.println("~ New Item assigned provisional ID: " + item.getId());
                }
            }
            
            order.addItem(item);
        }
        
        if (order.getItemsList().isEmpty()) {
            System.out.println("Order cancelled: No items were added.");
            return;
        }
        
        if (order instanceof OrderAccept && arrivedFile != null && arrivedFile.exists()) {
            String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd_HH-mm-ss"));
            String filename = "orders/accepted/accepted_" + arrivedOrderId + "_" + timestamp + ".txt";
            try {
                File dir = new File("orders/accepted");
                if (!dir.exists()) {
                    dir.mkdirs();
                }
                
                FileWriter writer = new FileWriter(filename);
                writer.write("=== Accepted Order ===\n");
                writer.write("Original Arrived ID: " + arrivedOrderId + "\n");
                writer.write("Date: " + timestamp + "\n");
                writer.write("Supplier: " + order.getSupplier() + "\n");
                writer.write("Items Accepted:\n");
                for (Items i : order.getItemsList()) {
                    writer.write(" - Name: " + i.getProductName() + ", Amount: " + i.getNumber() + "\n");
                }
                writer.close();
                System.out.println("Accepted order saved to: " + filename);
                
                File doneDir = new File("orders/done");
                if (!doneDir.exists()) doneDir.mkdirs();
                
                File doneFile = new File("orders/done/" + arrivedFile.getName());
                if (arrivedFile.renameTo(doneFile)) {
                    System.out.println("Original arrived order moved to 'done' folder.");
                } else {
                    System.out.println("Failed to move arrived order to 'done' folder.");
                }
            } catch (IOException e) {
                System.out.println("Error processing accepted order files: " + e.getMessage());
            }
        }
        
        if (order instanceof OrderNew) {
            String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd_HH-mm-ss"));
            String filename = "orders/new/order_" + timestamp + ".txt";
            try {
                File dir = new File("orders/new");
                if (!dir.exists()) {
                    dir.mkdirs();
                }
                
                FileWriter writer = new FileWriter(filename);
                writer.write("=== New Order ===\n");
                writer.write("Date: " + timestamp + "\n");
                writer.write("Supplier: " + order.getSupplier() + "\n");
                writer.write("Items:\n");
                for (Items i : order.getItemsList()) {
                    writer.write(" - Name: " + i.getProductName() + ", Amount: " + i.getNumber() + "\n");
                }
                writer.close();
                System.out.println("Order saved to: " + filename);
            } catch (IOException e) {
                System.out.println("Error saving order file: " + e.getMessage());
            }
        }
        
        if (order instanceof OrderReturn) {
            String timestamp = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd_HH-mm-ss"));
            String filename = "orders/returns/return_" + timestamp + ".txt";
            try {
                File dir = new File("orders/returns");
                if (!dir.exists()) {
                    dir.mkdirs();
                }
                
                FileWriter writer = new FileWriter(filename);
                writer.write("=== Return Order ===\n");
                writer.write("Date: " + timestamp + "\n");
                writer.write("Supplier: " + order.getSupplier() + "\n");
                writer.write("Reason: " + ((OrderReturn) order).getReturnReason() + "\n");
                writer.write("Items:\n");
                for (Items i : order.getItemsList()) {
                    writer.write(" - Name: " + i.getProductName() + ", Amount: " + i.getNumber() + "\n");
                }
                writer.close();
                System.out.println("Return order saved to: " + filename);
            } catch (IOException e) {
                System.out.println("Error saving return order file: " + e.getMessage());
            }
        }
        
        if (order instanceof StockModifier) {
            ((StockModifier) order).changeStock(storage);
            System.out.println("Order processed and stock was updated.");
        } else {
            System.out.println("New order recorded (awaiting eventual stock intake).");
        }
    }
}
