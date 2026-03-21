import java.util.ArrayList;
import java.util.List;

public abstract class BaseOrderWares {
    private static int idCounter = 1;
    private int id;
    private List<Items> itemsList = new ArrayList<>();
    private String supplier;

    public BaseOrderWares() {
        this.id = idCounter++;
    }

    public int getId() { return id; }
    public void setId(int id) { this.id = id; }

    public List<Items> getItemsList() { return itemsList; }
    public void setItemsList(List<Items> itemsList) { this.itemsList = itemsList; }
    public void addItem(Items item) { this.itemsList.add(item); }
    public String getSupplier() { return supplier; }
    public void setSupplier(String supplier) { this.supplier = supplier; }
}

class OrderNew extends BaseOrderWares implements Approve {
    public OrderNew(BaseUser user) {
        if (!checkPrivilege(user)) {
            throw new SecurityException("User does not have privilege to create an Order.");
        }
    }
}

class OrderReturn extends BaseOrderWares implements Approve, StockReducer {
    private String returnReason;

    public OrderReturn(BaseUser user) {
        if (!checkPrivilege(user)) {
            throw new SecurityException("User does not have privilege to create a Return.");
        }
    }

    public String getReturnReason() { return returnReason; }
    public void setReturnReason(String returnReason) { this.returnReason = returnReason; }
}

class OrderAccept extends BaseOrderWares implements StockAdder {
    public OrderAccept(BaseUser user) {
    }
}

interface Approve {
    default boolean checkPrivilege(BaseUser user) {
        return user.canApproveOrders();
    }
}

interface StockModifier {
    void changeStock(Storage storage);
}

interface StockAdder extends StockModifier {
    List<Items> getItemsList();

    default void changeStock(Storage storage) {
        for (Items item : getItemsList()) {
            storage.addItem(item);
        }
    }
}

interface StockReducer extends StockModifier {
    List<Items> getItemsList();

    default void changeStock(Storage storage) {
        for (Items item : getItemsList()) {
            storage.removeItem(item);
        }
    }
}
