import java.util.ArrayList;
import java.util.List;
public class Storage {
    private List<Items> productNames = new ArrayList<>();
    public List<Items> getProductNames() { return productNames; }
    
    private int nextIdCounter = 1;

    public int getNextAvailableId() {
        return nextIdCounter;
    }

    public Items findItemByName(String name) {
        for (Items item : productNames) {
            if (item.getProductName().equalsIgnoreCase(name)) {
                return item;
            }
        }
        return null;
    }
    
    private Items findMatchingItem(Items targetItem) {
        for (Items item : productNames) {
            boolean sameName = item.getProductName().equals(targetItem.getProductName());
            if (sameName) return item;
        }
        return null;
    }
    public Items findItemById(int id) {
        for (Items item : productNames) {
            if (item.getId() == id) {
                return item;
            }
        }
        return null;
    }
    public void addItem(Items itemToAdd) {
        Items existingItem = findMatchingItem(itemToAdd);
        if (existingItem != null) {
            existingItem.setNumber(existingItem.getNumber() + itemToAdd.getNumber());
        } else {
            if (itemToAdd.getId() == 0 || findItemById(itemToAdd.getId()) != null) {
                itemToAdd.setId(nextIdCounter++);
            } else if (itemToAdd.getId() >= nextIdCounter) {
                nextIdCounter = itemToAdd.getId() + 1;
            }
            productNames.add(itemToAdd);
        }
    }
    public void removeItem(Items itemToRemove) {
        Items existingItem = findMatchingItem(itemToRemove);
        if (existingItem != null) {
            existingItem.setNumber(Math.max(0, existingItem.getNumber() - itemToRemove.getNumber()));
        }
    }
    public int getNumber() {
        int sum = 0;
        if (productNames != null) {
            for (Items item : productNames) {
                sum += item.getNumber();
            }
        }
        return sum;
    }
    public void decreaseStockById(int id, int amount) {
        Items item = findItemById(id);
        if (item != null) {
            item.setNumber(Math.max(0, item.getNumber() - amount));
        }
    }
    public void increaseStockById(int id, int amount) {
        Items item = findItemById(id);
        if (item != null) {
            item.setNumber(item.getNumber() + amount);
        }
    }
}
class Items {
    private int id;
    private String productName;
    private int number;

    public Items() {
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }
    public String getProductName() { return productName; }
    public void setProductName(String productName) { this.productName = productName; }
    public int getNumber() { return number; }
    public void setNumber(int number) { this.number = number; }
}
