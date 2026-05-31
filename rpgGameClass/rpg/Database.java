package rpg;

import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;

/**
 * Klasa Database odpowiedzialna za komunikację z bazą danych MongoDB.
 * 
 * Funkcje:
 * - Zarządzanie połączeniem z bazą danych MongoDB Atlas
 * - Zapisywanie i odczytywanie stanu początkowego tokenów (postaci)
 * - Implementacja wzorca Singleton - gwarantuje jedną instancję bazy danych
 * - Obsługa kolekcji 'initial_tokens' do przechowywania stanu gry
 * 
 * Wzorzec Singleton zapewnia, że w całej aplikacji korzystamy ze spójnego dostępu
 * do bazy danych poprzez Database.getInstance()
 */
public class Database {
    // Jedyna instancja bazy danych (Singleton)
    private static Database instance;
    
    // Klient MongoDB - zarządza połączeniem z bazą danych
    private MongoClient mongoClient;
    
    // Referencja do bazy danych "obiektowe"
    private MongoDatabase database;
    
    // Kolekcja do przechowywania stanu początkowego tokenów
    // Zawiera dokumenty z danymi: name, maxHp, hp, x, y
    private MongoCollection<Document> tokensCollection;

    /**
     * Konstruktor prywatny - inicjalizuje połączenie z bazą danych MongoDB.
     * Jest prywatny aby zapobiec bezpośredniemu tworzeniu instancji (Singleton pattern).
     * 
     * Automatycznie wywoływany tylko raz przy pierwszym wołaniu getInstance().
     */
    private Database() {
        // Tworzy klienta MongoDB z użyciem adresu URL MongoDB Atlas
        this.mongoClient = MongoClients.create("mongodb+srv://Minotaur:Obiektowe@obiektowe.i0ebfgr.mongodb.net/");
        
        // Pobiera referencję do bazy danych "obiektowe"
        this.database = mongoClient.getDatabase("obiektowe");
        
        // Pobiera lub tworzy kolekcję "initial_tokens" do przechowywania stanu tokenów
        this.tokensCollection = database.getCollection("initial_tokens");
    }

    /**
     * Metoda statyczna implementująca wzorzec Singleton.
     * Zwraca jedyną instancję klasy Database.
     * Tworzy instancję tylko przy pierwszym wołaniu.
     * 
     * @return Jedyna instancja klasy Database
     */
    public static Database getInstance() {
        if (instance == null) {
            // Tworzenie nowej instancji - wywoła się konstruktor prywatny
            instance = new Database();
        }
        return instance;
    }

    /**
     * Sprawdza, czy w bazie danych istnieją już zapisane dane początkowe tokenów.
     * 
     * @return true jeśli w kolekcji initial_tokens istnieje co najmniej jeden dokument,
     *         false jeśli kolekcja jest pusta
     */
    public boolean hasInitialTokens() {
        // countDocuments() zwraca liczbę dokumentów w kolekcji
        return tokensCollection.countDocuments() > 0;
    }

    /**
     * Zapisuje stan początkowy tokena do bazy danych.
     * Przechowuje: nazwę, max HP, obecne HP oraz pozycję na mapie.
     * 
     * Wywoływana tylko raz przy pierwszym uruchomieniu gry dla każdego tokena.
     * 
     * @param t Token (postać) do zapisania
     */
    public void saveInitialToken(Token t) {
        // Tworzy dokument BSON (format bazy MongoDB) z danymi tokena
        Document doc = new Document("name", t.name)
                .append("maxHp", t.maxHp)  // Maksymalny HP tokena
                .append("hp", t.hp)        // Obecny HP tokena
                .append("x", t.x)          // Pozycja X na siatce
                .append("y", t.y);         // Pozycja Y na siatce
        
        // Wstawia dokument do kolekcji
        tokensCollection.insertOne(doc);
    }

    /**
     * Wczytuje i aplikuje zapisany stan początkowy tokena z bazy danych.
     * 
     * Szuka dokumentu o takiej samej nazwie tokena i przywraca jego właściwości.
     * Jeśli nie znajdzie dokumentu, token pozostaje niezmieniony.
     * 
     * @param t Token (postać) do wczytania i zaktualizowania
     */
    public void applyInitialTokenData(Token t) {
        // Szuka dokumentu z kolekcji, gdzie nazwa odpowiada nazwie tokena
        Document doc = tokensCollection.find(new Document("name", t.name)).first();
        
        // Jeśli dokument istnieje - przywróć jego wartości
        if (doc != null) {
            // getInteger() zwraca wartość z dokumentu, drugi parametr to wartość domyślna
            t.maxHp = doc.getInteger("maxHp", t.maxHp);
            t.hp = doc.getInteger("hp", t.hp);
            t.x = doc.getInteger("x", t.x);
            t.y = doc.getInteger("y", t.y);
        }
    }

    /**
     * Zamyka połączenie z bazą danych MongoDB.
     * 
     * Powinno być wywoływane przy zamykaniu aplikacji aby prawidłowo zwolnić zasoby.
     * Bezpiecznie sprawdza, czy klient nie jest null zanim go zamyka.
     */
    public void close() {
        // Upewnij się, że klient istnieje zanim go zamykamy
        if (this.mongoClient != null) {
            // Zamyka połączenie i zwolnia zasoby
            this.mongoClient.close();
        }
    }
}
