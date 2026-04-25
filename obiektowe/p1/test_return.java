public class test_return {
    public static void main(String[] args) {
        Storage storage = new Storage();
        Items item = new Items();
        item.setProductName("Test");
        item.setNumber(10);
        storage.addItem(item);
        
        System.out.println(storage.findItemByName("Test").getNumber());
        
        Admin user = new Admin();
        OrderReturn order = new OrderReturn(user);
        Items retItem = new Items();
        retItem.setProductName("Test");
        retItem.setNumber(2);
        order.addItem(retItem);
        order.changeStock(storage);
        
        System.out.println(storage.findItemByName("Test").getNumber());
    }
}
