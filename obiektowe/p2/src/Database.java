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

/**
 * Klasa Database operująca jako połączenie ze stystemem Bazy Danych (np. MongoDB).
 * Wykorzystuje silny wzorzec Singleton, upewniając się, że korzystamy ze spójnego dostępu do instancji z danymi
 * (w przypadku obecnego działania in-memory zapewnia ciągłość trzymanych obiektów jako pojedyncze źródło prawdy).
 */
public class Database {
    private static Database instance;
    private MongoClient mongoClient;
    private MongoDatabase database;
    private MongoCollection<Document> ordersCollection;

    /**
     * Prywatny konstruktor (wzorzec Singleton).
     * Inicjalizuje połączenie z klastrem MongoDB Atlas za pomocą connection string.
     * Ustawia bazę danych "obiektowe" i kolekcję "orders" dla przechowywania zleceń.
     * Pula połączeń domyślnie wynosi 100, co jest wystarczające dla prostych przypadków użycia.
     */
    private Database() {
        // Łączenie się z MongoDB Atlas
        this.mongoClient = MongoClients.create("mongodb+srv://Minotaur:Obiektowe@obiektowe.i0ebfgr.mongodb.net/");
        this.database = mongoClient.getDatabase("obiektowe");
        this.ordersCollection = database.getCollection("orders");
    }

    /**
     * Publiczna metoda statyczna implementująca wzorzec Singleton.
     * Zwraca jedyną instancję Database - gwarantując jedno połączenie do bazy dla całej aplikacji.
     * Jeśli instancja jeszcze nie istnieje, tworzy ją (lazy initialization).
     */
    public static Database getInstance() {
        if (instance == null) {
            instance = new Database();
        }
        return instance;
    }

    /**
     * Prywatna metoda generująca unikalny, autoinkrementacyjny identyfikator dla każdego nowego zlecenia.
     * Pracuje z kolekcją "counters" w bazie, która przechowuje sekwencję numerów ID.
     * Atomowo inkrementuje wartość seq dla ID "orderId" i zwraca poprzednią wartość.
     * Jeśli licznik nie istnieje, inicjalizuje go wartością 2 i zwraca 1 dla pierwszego zlecenia.
     */
    private int getNextId() {
        Document counter = database.getCollection("counters").findOneAndUpdate(
                new Document("_id", "orderId"),
                new Document("$inc", new Document("seq", 1))
        );
        if (counter == null) {
    /**
     * Dodaje nowe zlecenie do bazy danych.
     * Generuje unikalny ID, bierze obecny czas jako czas utworzenia (time1Creation).
     * Tworzy obiekt Order i dokument MongoDB z wszystkimi polami inicjalizowanymi.
     * Stan początkowy to NOT_STARTED, komentarz operatora oraz inne pola czasowe są null.
     * 
     * @param firstName Imię klienta
     * @param lastName Nazwisko klienta
     * @param comment Komentarz/opis zgłoszenia od klienta
     * @return Nowo utworzony obiekt Order
     */
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
    /**
     * Aktualizuje istniejące zlecenie w bazie MongoDB.
     * Operuje na polu $set, który ustawia nowe wartości dla komentarzy, czasów i stanu.
     * Konwertuje obiekty LocalDateTime na Date dla zgodności z MongoDB.
     * Wyszukuje dokument po ID (_id) i zastępuje odpowiednie pola.
     * 
     * @param order Obiekt Order zawierający zaktualizowane dane
     */
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
    /**
     * Prywatna metoda mapująca dokument MongoDB na obiekt Order.
     * Konwertuje pola z dokumentu (Including Date objects) na odpowiednie typy w Order.
     * Obsługuje nullowe wartości dla pól czasowych (jeśli operacja nie została jeszcze rozpoczęta/ukończona).
     * Konwertuje Date z bazy na LocalDateTime dla lokalnej strefy czasowej.
     * 
     * @param doc Dokument MongoDB pobrany z kolekcji
     * @return Obiekt Order zmapowany z dokumentu
     */
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
    /**
     * Pobiera wszystkie zlecenia z bazy danych.
     * Iteruje przez wszystkie dokumenty w kolekcji i mapuje je na obiekty Order.
     * 
     * @return Lista wszystkich zleceń
     */
    public List<Order> getOrders() {
        List<Order> orders = new ArrayList<>();
        for (Document doc : ordersCollection.find()) {
            orders.add(mapToOrder(doc));
        }
        return orders;
    }

    /**
     * Pobiera zlecenie z bazy po unikalnym ID.
    /**
     * Usuwa jedno zlecenie z bazy danych.
     * Wyszukuje po ID i permanentnie usuwa dokument.
     * 
     * @param order Objekt Order do usunięcia
     */
    public void removeOrder(Order order) {
        ordersCollection.deleteOne(new Document("_id", order.getId()));
    }
    
    /**
     * Usuwa wszystkie niezakończone zlecenia danego klienta (po imienia i nazwisku).
     * Administrator może użyć tej metody do wyczyszczenia danych klienta.
     * Tylko zlecenia w stanie innym niż COMPLETED są usuwane.
     * 
     * @param firstName Imię klienta
     * @param lastName Nazwisko klienta
     */
    public void deleteClientData(String firstName, String lastName) {
        ordersCollection.deleteMany(
            new Document("clientFirstName", firstName)
                .append("clientLastName", lastName)
                .append("state", new Document("$ne", OrderState.COMPLETED.name()))
        );
    }

    /**
     * Zamyka połączenie z MongoDB i zwalnia zasoby puli połączeń.
     * Powinna być wywoływana przed zamknięciem aplikacji.
     */        return orders;
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
