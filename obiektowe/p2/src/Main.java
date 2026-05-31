import java.time.LocalDateTime;
import java.util.List;
import java.util.Scanner;

/**
 * Główna klasa uruchomieniowa dla Projektu 2 (System Zarządzania Zleceniami).
 * Projekt prezentuje rozwiązanie oparte o rozbudowany model dziedziny wykorzystując zaawansowane relacje między obiektami.
 * Reprezentuje relacje w modelu klient-operator-administrator, gdzie cykl życia zlecenia zależy od statusów modyfikowanych
 * przez poszczególne role w procesie. 
 * 
 * Główne funkcjonalności systemu to m.in.:
 * - Logowanie w roli Klienta, Operatora bądź Administratora przy pomocy komendy.
 * - Klient uprawniony jest do tworzenia nowch zleceń, modyfikacji czy też ich edycji/opóźniania.
 * - Opertor zajmuje się przepisywaniem estymat czasu rozwiązania zadania. Zlecenia mogą być "przyjmowane do realizacji".
 * - Administratorzy posiadają pełne prawa usuwania zgłoszeń i klientów, działając niczym bóg systemu.
 * - Baza daych mockowana jest w klasie Database dla ułatwienia testów (in-memory test db).
 * 
 * Architektura oparta o wzorzec interaktywnej powłoki (REPL) - użytkownik wpisuje komendy bezpośrednio do konsoli, 
 * które następnie delegowane są do logiki odpowiednich klas ról posiadających daną sesję.
 */
public class Main {
    public static void main(String[] args) {
        Database db = Database.getInstance();
        Scanner scanner = new Scanner(System.in);
        
        Client currentClient = null;
        Operator currentOperator = null;
        Admin currentAdmin = null;

        System.out.println("System Zarządzania Zleceniami zainicjowany.");
        System.out.println("Dostępne polecenia:");
        System.out.println("  login_client <imie> <nazwisko>");
        System.out.println("  login_operator");
        System.out.println("  login_admin");
        System.out.println("  client_order <komentarz>");
        System.out.println("  client_edit <id> <nowy_komentarz>");
        System.out.println("  client_delay <id>");
        System.out.println("  operator_process <id> <komentarz_operatora>");
        System.out.println("  operator_estimate <id> <godziny_od_teraz>");
        System.out.println("  operator_delay <id>");
        System.out.println("  operator_edit <id> <nowy_komentarz>");
        System.out.println("  operator_complete <id>");
        System.out.println("  admin_delete_order <id>");
        System.out.println("  admin_delete_client <imie> <nazwisko>");
        System.out.println("  list - wypisuje wszystkie zlecenia w bazie");
        System.out.println("  logout - wylogowuje obecnego użytkownika");
        System.out.println("  exit - zamyka program");
        
        while (true) {
            System.out.print("\n> ");
            String line = scanner.nextLine().trim();
            if (line.isEmpty()) continue;
            
            String[] parts = line.split("\\s+", 2);
            String cmd = parts[0];
            String argsStr = parts.length > 1 ? parts[1] : "";
            
            try {
                switch (cmd) {
                    case "login_client":
                        if (currentClient != null || currentOperator != null || currentAdmin != null) {
                            System.out.println("Błąd: Ktoś jet już zalogowany. Użyj 'logout' najpierw.");
                            break;
                        }
                        String[] names = argsStr.split("\\s+", 2);
                        if (names.length == 2) {
                            currentClient = new Client(names[0], names[1], db);
                            System.out.println("Zalogowano jako klient: " + names[0] + " " + names[1]);
                        } else {
                            System.out.println("Błąd: użyj 'login_client <imie> <nazwisko>'");
                        }
                        break;
                    case "login_operator":
                        if (currentClient != null || currentOperator != null || currentAdmin != null) {
                            System.out.println("Błąd: Ktoś jet już zalogowany. Użyj 'logout' najpierw.");
                            break;
                        }
                        currentOperator = new Operator(db);
                        System.out.println("Zalogowano jako operator.");
                        break;
                    case "login_admin":
                        if (currentClient != null || currentOperator != null || currentAdmin != null) {
                            System.out.println("Błąd: Ktoś jet już zalogowany. Użyj 'logout' najpierw.");
                            break;
                        }
                        currentAdmin = new Admin(db);
                        System.out.println("Zalogowano jako administrator.");
                        break;
                    case "logout":
                        if (currentClient == null && currentOperator == null && currentAdmin == null) {
                            System.out.println("Nikt nie jest zalogowany.");
                        } else {
                            currentClient = null;
                            currentOperator = null;
                            currentAdmin = null;
                            System.out.println("Pomyślnie wylogowano.");
                        }
                        break;
                    case "client_order":
                        if (currentClient != null) {
                            Order o = currentClient.createOrder(argsStr);
                            System.out.println("Utworzono zlecenie o ID: " + o.getId());
                        } else if (currentOperator != null || currentAdmin != null) {
                            System.out.println("Błąd: Brak uprawnień! Jesteś zalogowany jako inna rola, to akcja klienta.");
                        } else {
                            System.out.println("Najpierw zaloguj się jako klient.");
                        }
                        break;
                    case "client_edit":
                        if (currentClient != null) {
                            String[] editParts = argsStr.split("\\s+", 2);
                            currentClient.editOrderComment(Integer.parseInt(editParts[0]), editParts[1]);
                            System.out.println("Zaktualizowano komentarz.");
                        } else if (currentOperator != null || currentAdmin != null) {
                            System.out.println("Błąd: Brak uprawnień! Jesteś zalogowany jako inna rola, to akcja klienta.");
                        } else {
                            System.out.println("Najpierw zaloguj się jako klient.");
                        }
                        break;
                    case "client_delay":
                        if (currentClient != null) {
                            currentClient.delayOrder(Integer.parseInt(argsStr));
                            System.out.println("Zmieniono status na opóźnione.");
                        } else if (currentOperator != null || currentAdmin != null) {
                            System.out.println("Błąd: Brak uprawnień! Jesteś zalogowany jako inna rola, to akcja klienta.");
                        } else {
                            System.out.println("Najpierw zaloguj się jako klient.");
                        }
                        break;
                    case "operator_process":
                         if (currentOperator != null) {
                            String[] procParts = argsStr.split("\\s+", 2);
                            currentOperator.processNewOrder(Integer.parseInt(procParts[0]), procParts[1]);
                            System.out.println("Operator przetworzył zlecenie.");
                        } else if (currentClient != null || currentAdmin != null) {
                            System.out.println("Błąd: Brak uprawnień! Jesteś zalogowany jako inna rola, to akcja operatora.");
                        } else {
                            System.out.println("Najpierw zaloguj się jako operator.");
                        }
                        break;
                    case "operator_estimate":
                        if (currentOperator != null) {
                            String[] estParts = argsStr.split("\\s+", 2);
                            currentOperator.estimateCompletion(Integer.parseInt(estParts[0]), LocalDateTime.now().plusHours(Integer.parseInt(estParts[1])));
                            System.out.println("Dodano szacowany czas zakończenia.");
                        } else if (currentClient != null || currentAdmin != null) {
                            System.out.println("Błąd: Brak uprawnień! Jesteś zalogowany jako inna rola, to akcja operatora.");
                        } else {
                            System.out.println("Najpierw zaloguj się jako operator.");
                        }
                        break;
                    case "operator_delay":
                         if (currentOperator != null) {
                            currentOperator.markAsDelayed(Integer.parseInt(argsStr));
                            System.out.println("Operator ustawił opóźnienie.");
                        } else if (currentClient != null || currentAdmin != null) {
                            System.out.println("Błąd: Brak uprawnień! Jesteś zalogowany jako inna rola, to akcja operatora.");
                        } else {
                            System.out.println("Najpierw zaloguj się jako operator.");
                        }
                        break;
                    case "operator_edit":
                         if (currentOperator != null) {
                            String[] editOpParts = argsStr.split("\\s+", 2);
                            currentOperator.editOperatorComment(Integer.parseInt(editOpParts[0]), editOpParts[1]);
                            System.out.println("Zaktualizowano komentarz operatora.");
                        } else if (currentClient != null || currentAdmin != null) {
                            System.out.println("Błąd: Brak uprawnień! Jesteś zalogowany jako inna rola, to akcja operatora.");
                        } else {
                            System.out.println("Najpierw zaloguj się jako operator.");
                        }
                        break;
                    case "operator_complete":
                        if (currentOperator != null) {
                            currentOperator.completeOrder(Integer.parseInt(argsStr));
                            System.out.println("Zlecenie zakończone.");
                        } else if (currentClient != null || currentAdmin != null) {
                            System.out.println("Błąd: Brak uprawnień! Jesteś zalogowany jako inna rola, to akcja operatora.");
                        } else {
                            System.out.println("Najpierw zaloguj się jako operator.");
                        }
                        break;
                    case "admin_delete_order":
                        if (currentAdmin != null) {
                            currentAdmin.deleteOrder(Integer.parseInt(argsStr));
                            System.out.println("Usunięto zlecenie (jeśli istniało i nie było zakończone).");
                        } else if (currentClient != null || currentOperator != null) {
                            System.out.println("Błąd: Brak uprawnień! Jesteś zalogowany jako inna rola, to akcja administratora.");
                        } else {
                            System.out.println("Najpierw zaloguj się jako administrator.");
                        }
                        break;
                    case "admin_delete_client":
                         if (currentAdmin != null) {
                            String[] delParts = argsStr.split("\\s+", 2);
                            currentAdmin.removeClient(delParts[0], delParts[1]);
                            System.out.println("Usunięto niezakończone zlecenia klienta.");
                        } else if (currentClient != null || currentOperator != null) {
                            System.out.println("Błąd: Brak uprawnień! Jesteś zalogowany jako inna rola, to akcja administratora.");
                        } else {
                            System.out.println("Najpierw zaloguj się jako administrator.");
                        }
                        break;
                    case "list":
                        List<Order> orders = db.getOrders();
                        System.out.println("Wszystkie zlecenia (" + orders.size() + "):");
                        for (Order order : orders) {
                            System.out.println("ID:" + order.getId() + " [" + order.getState() + "] Klient:" + order.getClientFirstName() + " " + order.getClientLastName() + 
                                " Kom:" + order.getClientComment() + " OpKom:" + order.getOperatorComment() + " Czas1:" + order.getTime1Creation() + " Czas2: " + order.getTime2Start() + " Czas3: " + order.getTime3EstimatedCompletion());
                        }
                        break;
                    case "exit":
                        System.out.println("Zamykanie programu i rozłączanie z bazą...");
                        db.close();
                        return;
                    default:
                        System.out.println("Nieznane polecenie.");
                }
            } catch (Exception e) {
                System.out.println("Błąd podczas wgrywania komendy: " + e.getMessage());
            }
        }
    }
}
