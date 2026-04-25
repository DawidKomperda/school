import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Optional;

import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;

public class Database {
    private static Database instance;
    private MongoClient mongoClient;
    private MongoDatabase database;
    private MongoCollection<Document> ordersCollection;

    private Database() {
        // Connecting to MongoDB Atlas
        // Connection pool defaults to 100 max connections, which is sufficient for simple use cases.
        this.mongoClient = MongoClients.create("mongodb+srv://Minotaur:Obiektowe@obiektowe.i0ebfgr.mongodb.net/");
        this.database = mongoClient.getDatabase("obiektowe");
        this.ordersCollection = database.getCollection("orders");
    }

    public static Database getInstance() {
        if (instance == null) {
            instance = new Database();
        }
        return instance;
    }

    private int getNextId() {
        Document counter = database.getCollection("counters").findOneAndUpdate(
                new Document("_id", "orderId"),
                new Document("$inc", new Document("seq", 1))
        );
        if (counter == null) {
            database.getCollection("counters").insertOne(new Document("_id", "orderId").append("seq", 2));
            return 1;
        }
        return counter.getInteger("seq");
    }

    public Order addOrder(String firstName, String lastName, String comment) {
        int newId = getNextId();
        LocalDateTime now = LocalDateTime.now();
        Order order = new Order(newId, firstName, lastName, comment, now);

        Document doc = new Document("_id", newId)
                .append("clientFirstName", firstName)
                .append("clientLastName", lastName)
                .append("clientComment", comment)
                .append("operatorComment", null)
                .append("time1Creation", Date.from(now.atZone(ZoneId.systemDefault()).toInstant()))
                .append("time2Start", null)
                .append("time3EstimatedCompletion", null)
                .append("state", order.getState().name());

        ordersCollection.insertOne(doc);
        return order;
    }

    public void updateOrder(Order order) {
        Document updateDoc = new Document("$set", new Document("clientComment", order.getClientComment())
                .append("operatorComment", order.getOperatorComment())
                .append("time2Start", order.getTime2Start() != null ? Date.from(order.getTime2Start().atZone(ZoneId.systemDefault()).toInstant()) : null)
                .append("time3EstimatedCompletion", order.getTime3EstimatedCompletion() != null ? Date.from(order.getTime3EstimatedCompletion().atZone(ZoneId.systemDefault()).toInstant()) : null)
                .append("state", order.getState().name()));

        ordersCollection.updateOne(new Document("_id", order.getId()), updateDoc);
    }

    private Order mapToOrder(Document doc) {
        Order order = new Order(
                doc.getInteger("_id"),
                doc.getString("clientFirstName"),
                doc.getString("clientLastName"),
                doc.getString("clientComment"),
                doc.getDate("time1Creation") != null ? doc.getDate("time1Creation").toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime() : null
        );
        order.setOperatorComment(doc.getString("operatorComment"));
        
        if (doc.getDate("time2Start") != null) {
            order.setTime2Start(doc.getDate("time2Start").toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime());
        }
        if (doc.getDate("time3EstimatedCompletion") != null) {
            order.setTime3EstimatedCompletion(doc.getDate("time3EstimatedCompletion").toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime());
        }
        order.setState(OrderState.valueOf(doc.getString("state")));
        return order;
    }

    public List<Order> getOrders() {
        List<Order> orders = new ArrayList<>();
        for (Document doc : ordersCollection.find()) {
            orders.add(mapToOrder(doc));
        }
        return orders;
    }

    public Optional<Order> getOrderById(int id) {
        Document doc = ordersCollection.find(new Document("_id", id)).first();
        if (doc != null) {
            return Optional.of(mapToOrder(doc));
        }
        return Optional.empty();
    }

    public void removeOrder(Order order) {
        ordersCollection.deleteOne(new Document("_id", order.getId()));
    }
    
    public void deleteClientData(String firstName, String lastName) {
        ordersCollection.deleteMany(
            new Document("clientFirstName", firstName)
                .append("clientLastName", lastName)
                .append("state", new Document("$ne", OrderState.COMPLETED.name()))
        );
    }

    public void close() {
        if (this.mongoClient != null) {
            this.mongoClient.close();
        }
    }
}
