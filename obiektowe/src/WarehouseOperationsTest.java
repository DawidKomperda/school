import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
public class WarehouseOperationsTest {
    private Admin admin;
    private Manager manager;
    private Employee employee;
    private Storage storage;
    @BeforeEach
    public void setUp() {
        admin = new Admin();
        manager = new Manager();
        employee = new Employee();
        storage = new Storage();
    }
    @Test
    public void testEmployeeOperations() {
        System.out.println("--- Testing Employee Operations ---");
        OrderAccept accept = new OrderAccept(admin);
        assertThrows(SecurityException.class, () -> {
            new OrderNew(employee);
        }, "Employee should NOT be allowed to order.");
        System.out.println("Blocked: Employee was denied creating an Order.");
        Items item = new Items();
        item.setProductName("Mouse");
        item.setNumber(10);
        accept.addItem(item);  
        accept.changeStock(storage);
        assertEquals(10, storage.getNumber(), "Employee successfully accepted items.");
        System.out.println("Success: Employee accepted 10 Mouse units.");
        assertThrows(SecurityException.class, () -> {
            new OrderReturn(employee);
        }, "Employee should NOT be allowed to approve returns.");
        System.out.println("Blocked: Employee was denied processing a Return.");
        assertEquals(10, storage.getNumber(), "Storage should still be 10 since the return was denied.");
    }
    @Test
    public void testManagerOperations() {
        System.out.println("--- Testing Manager Operations ---");
        OrderAccept accept = new OrderAccept(admin);
        OrderNew order = new OrderNew(manager);
        assertNotNull(order, "Manager should be allowed to order.");
        Items item = new Items();
        item.setProductName("Keyboard");
        item.setNumber(20);
        accept.addItem(item);  
        accept.changeStock(storage);
        assertEquals(20, storage.getNumber(), "Manager successfully accepted items.");
        OrderReturn returnItem = new OrderReturn(manager);
        Items returnStock = new Items();
        returnStock.setProductName("Keyboard");
        returnStock.setNumber(5);
        returnItem.addItem(returnStock); returnItem.changeStock(storage);
        assertEquals(15, storage.getNumber(), "Manager successfully returned items, reducing stock.");
    }
    @Test
    public void testAdminOperations() {
        System.out.println("--- Testing Admin Operations ---");
        OrderAccept accept = new OrderAccept(admin);
        OrderNew order = new OrderNew(admin);
        assertNotNull(order, "Admin should be allowed to order.");
        Items item = new Items();
        item.setProductName("Monitor");
        item.setNumber(30);
        accept.addItem(item);  
        accept.changeStock(storage);
        assertEquals(30, storage.getNumber(), "Admin successfully accepted items.");
        OrderReturn returnItem = new OrderReturn(admin);
        Items returnStock = new Items();
        returnStock.setProductName("Monitor");
        returnStock.setNumber(10);
        returnItem.addItem(returnStock); returnItem.changeStock(storage);
        assertEquals(20, storage.getNumber(), "Admin successfully returned items, reducing stock.");
    }
    @Test
    public void testAcceptMilkWithDifferentDates() {
        System.out.println("--- Testing Accept Milk with Expiration Dates ---");
        OrderAccept accept = new OrderAccept(admin);
        Items milkBatch1 = new Items();
        milkBatch1.setProductName("Milk");
        milkBatch1.setNumber(10);
        Items milkBatch2 = new Items();
        milkBatch2.setProductName("Milk");
        milkBatch2.setNumber(15);
        Items milkBatch3 = new Items();
        milkBatch3.setProductName("Milk");
        milkBatch3.setNumber(12);
        accept.addItem(milkBatch1);  
        accept.addItem(milkBatch2);  
        accept.addItem(milkBatch3);  
        accept.changeStock(storage);
        assertEquals(37, storage.getNumber(), "Storage should sum the numbers from all distinct milk batches.");
        employee.setUsername("John Employee");
        employee.displayStock(storage);
        manager.displayStock(storage);
    }
    @Test
    public void testSellAndReturnById() {
        System.out.println("--- Testing User itemSell and itemReturn ---");
        OrderAccept accept = new OrderAccept(admin);
        Items keyboard = new Items();
        keyboard.setId(101);
        keyboard.setProductName("Mechanical Keyboard");
        keyboard.setNumber(50);
        accept.addItem(keyboard);  
        accept.changeStock(storage);
        assertEquals(50, storage.getNumber(), "Storage should start with 50 keyboards.");
        employee.itemSell(101, 10, storage);
        assertEquals(40, storage.getNumber(), "Storage should have 40 keyboards after Employee sells 10.");
        manager.itemSell(101, 15, storage);
        assertEquals(25, storage.getNumber(), "Storage should have 25 keyboards after Manager sells 15.");
        admin.itemReturn(101, 5, storage);
        assertEquals(30, storage.getNumber(), "Storage should have 30 keyboards after Admin returns 5 to stock.");
    }
    @Test
    public void testManageWaresPermissions() {
        System.out.println("--- Testing User manageWares ---");
        OrderAccept accept = new OrderAccept(admin);
        Items keyboard = new Items();
        keyboard.setId(101);
        keyboard.setProductName("Mechanical Keyboard");
        keyboard.setNumber(50);
        accept.addItem(keyboard);  
        accept.changeStock(storage);
        
        assertFalse(employee instanceof WareManager, "Employee should NOT implement WareManager.");
        assertTrue(manager instanceof WareManager, "Manager should implement WareManager.");
        assertTrue(admin instanceof WareManager, "Admin should implement WareManager.");
        
        java.io.InputStream savedStandardInputStream = System.in;
        
        try {
            System.setIn(new java.io.ByteArrayInputStream("101\n1\nNew Keyboard\n".getBytes()));
            assertDoesNotThrow(() -> {
                ((WareManager) manager).manageWares(storage);
            }, "Manager should be allowed to manage wares.");
            
            System.setIn(new java.io.ByteArrayInputStream("101\n2\n200\n".getBytes()));
            assertDoesNotThrow(() -> {
                ((WareManager) admin).manageWares(storage);
            }, "Admin should be allowed to manage wares.");
        } finally {
            System.setIn(savedStandardInputStream);
        }
    }
    @Test
    public void testEditStorageDetailPermissions() {
        System.out.println("--- Testing User editStorageDetail ---");
        OrderAccept accept = new OrderAccept(admin);
        Items keyboard = new Items();
        keyboard.setId(101);
        keyboard.setProductName("Mechanical Keyboard");
        keyboard.setNumber(50);
        accept.addItem(keyboard);  
        accept.changeStock(storage);
        
        assertFalse(employee instanceof WareManager, "Employee should NOT implement WareManager.");
        
        ((WareManager) manager).editStorageDetail(storage, 101, "Cool Keyboard", 100);
        assertEquals(100, storage.getNumber(), "Storage total amount should be updated by Manager.");
        
        ((WareManager) admin).editStorageDetail(storage, 101, "Gaming Keyboard", 40);
        assertEquals(40, storage.getNumber(), "Storage total amount should be updated by Admin.");
    }
}
