# Sprawozdanie z projektu: System Zarządzania Zleceniami

## 1. Cel projektu
Celem projektu było zaprojektowanie i zaimplementowanie w języku Java aplikacji konsolowej umożliwiającej zarządzanie zleceniami usług (np. napraw serwisowych). System musiał w sposób trwały przechowywać dane, do czego wykorzystano nierelacyjną bazę danych MongoDB (w chmurze MongoDB Atlas). Aplikacja została zbudowana zgodnie z paradygmatami programowania obiektowego (OOP) z uwzględnieniem bezpiecznego podziału na role dla użytkowników końcowych.

## 2. Wykorzystane technologie i narzędzia
* **Język programowania:** Java 11
* **Zarządzanie zależnościami i budowanie:** Apache Maven
* **Baza danych:** MongoDB (Atlas)
* **Sterownik bazy danych:** `mongodb-driver-sync`
* **Projektowanie/modelowanie:** diagramy UML (Mermaid.js / diagrams.net)

## 3. Architektura i projektowanie obiektowe
Aplikacja została oparta na solidnych fundamentach programowania obiektowego. Rozdzielono w niej warstwę logiczną i danych od zarządzania widokiem/konsolą.

Główne mechanizmy użyte w projekcie:
* **Dziedziczenie i Polimorfizm:** Zaprojektowano hierarchię ról użytkowników. Klasa `Admin` rozszerza (`extends`) klasę `Operator`, co pozwala administratorowi na korzystanie ze wszystkich funkcjonalności dostępnych typowemu pracownikowi (operatorowi), a ponadto dodaje uprawnienia najwyższego szczebla (np. całkowite usunięcie wybranych danych).
* **Kompozycja:** Klasa `Database` zarządza globalnie cyklem życia i przechowywaniem wszystkich obiektów typu `Order` (Zlecenie). W diagramie UML zostało to wyrażone twardą formą kompozycji (1 do *), gdzie system ulega uszkodzeniu persystencji przy awarii bazy.
* **Typy Wyliczeniowe (Enum):** Wprowadzono klasę `OrderState` przechowującą zbiór dozwolonych stanów zlecenia w trakcie jego cyklu życia (np. nowo utworzone, w trakcie przetwarzania, opóźnione, zakończone).
* **Hermetyzacja:** Dane o zleceniu zostały odpowiednio ukryte w polach prywatnych i zabezpieczone właściwymi metodami do ich podglądu lub modyfikacji w zależności od uprawnień edytora.

## 4. Funkcjonalności systemu (Role-Based Access Control)
System został zabezpieczony za pomocą autoryzacji bazującej na jednej aktywnej sesji naraz i sztywnym wydzieleniu komend, by zminimalizować ryzyko manipulacji zleceniem przez nieuwierzytelnioną rolę.

1. **Klient:**
   * Rejestracja/logowanie (`login_client`).
   * Zgłaszanie nowych zleceń z początkowym komentarzem opisującym awarię.
   * Edycja komentarza i zgłaszanie opóźnień do własnych spraw.
2. **Operator (Serwisant):**
   * Przyjęcie zlecenia od klienta do weryfikacji (`operator_process`).
   * Określenie czasu na realizację naprawy/zlecenia (`operator_estimate`).
   * Raportowanie opóźnień (ustawia specyficzny stan w obiekcie) oraz ewentualnego finalnego zakończenia naprawy (`operator_complete`).
3. **Administrator:**
   * Dziedziczy komendy operatora.
   * Może bezkompromisowo usuwać poszczególne zlecenia (`admin_delete_order`).
   * Posiada możliwość kasowania profili i wsadu pełnych użytkowników (klientów).

## 5. Przebieg i realizacja
Podczas prac deweloperskich projekt został zintegrowany z menedżerem pakietów Maven. 
Utworzono połączenie sieciowe z repozytorium Atlas za pomocą odpowiedniego Connection Stringa.
Skonfigurowano pętlę REPL (Read-Eval-Print Loop) w głównej klasie `Main`, co pozwala na symulację serwera terminalowego przez wydawanie ciągłych komend konwersacyjnych. Zadbano również o odpowiednie zamykanie wątków sterownika MongoDB przy zamykaniu programu (przechwytywanie poprawnego sygnału `exit`).
Zwieńczeniem całości projektu było odpowiednie uformowanie logiki w struktury wizualne za pomocą diagramów klas UML.

## 6. Możliwe plany rozwoju
Aplikację w przyszłych wersjach można z łatwością rozwijać o wprowadzanie silnych masek walidacyjnych przy loginie (np. autentykacja na hasło + hash). Można również zastąpić konsolowy interfejs rozwiązaniem opartym na graficznym oknie Swing / JavaFX lub przekształcić projekt w pełnoprawne REST API przy użyciu frameworka Spring Boot.

## 7. Podsumowanie
Projekt został w pełni zrealizowany zgodnie z zaleceniami paradygmatów obiektowych. Narzędzia konsolowe są stabilne, potrafią filtrować i komunikować błędy użytkownika bez wyłączania procesu (`Exception handling`). Komunikacja online z bazą danych MongoDB przebiega bez problemów, realizując z sukcesem model utrwalania informacji z aplikacji obiektowej.