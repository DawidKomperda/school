package rpg;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.List;

/**
 * Główne okno aplikacji i centralny kontroler rozgrywki.
 *
 * Klasa odpowiada za:
 * - tworzenie i inicjalizację tokenów
 * - utrzymywanie kolejki tur i rund
 * - wykonywanie akcji oraz ruchów
 * - synchronizację UI z aktualnym stanem gry
 * - uruchomienie całej aplikacji Swing
 */
public class Game extends JFrame {

    // Lista tokenów aktualnie obecnych na planszy, w kolejności inicjatywy
    List<Token> tokens; // Package-private for BoardPanel
    
    // Panele interfejsu użytkownika
    private JPanel initiativePanel;
    private JPanel actionPanel;
    private JList<Token> initiativeList;
    private DefaultListModel<Token> listModel;
    BoardPanel boardPanel;
    
    // Stan rozgrywki: aktualna runda i liczba wykonanych tur w tej rundzie
    private int currentRound = 1;
    private int turnsTakenThisRound = 0;
    
    // Dane interakcji współdzielone z BoardPanel
    Token selectedToken = null;
    Action selectedAction = null;
    Map<Point, Integer> validMoves = new HashMap<>();
    Set<Point> validActionRange = new HashSet<>();
    Point hoverGrid = new Point(-1, -1);

    /**
     * Konfiguruje główne okno gry, tworzy tokeny i składa cały interfejs Swing.
     */
    public Game() {
        // Tytuł okna oraz podstawowe ustawienia JFrame
        setTitle("D&D Style RPG Game");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Tworzy początkowy zestaw tokenów, pobierając stan startowy z bazy
        initTokens();

        // Górny pasek z przyciskiem kończenia tury
        JPanel topPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        JButton endTurnBtn = new JButton("End Turn");
        endTurnBtn.addActionListener(e -> endTurn());
        topPanel.add(endTurnBtn);
        add(topPanel, BorderLayout.NORTH);

        // Panel inicjatywy po lewej stronie - pokazuje kolejność tur
        initiativePanel = new JPanel(new BorderLayout());
        initiativePanel.setPreferredSize(new Dimension(200, 0));
        initiativePanel.setBorder(BorderFactory.createTitledBorder("Initiative - Turn " + currentRound));
        
        listModel = new DefaultListModel<>();
        for (Token t : tokens) {
            listModel.addElement(t);
        }
        
        initiativeList = new JList<>(listModel);
        // Własny renderer pozwala kontrolować sposób prezentacji tokenów na liście
        initiativeList.setCellRenderer(new TokenListRenderer());
        initiativePanel.add(new JScrollPane(initiativeList), BorderLayout.CENTER);
        add(initiativePanel, BorderLayout.WEST);

        // Panel akcji na dole - dynamicznie pokazuje akcje wybranego tokena
        actionPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        actionPanel.setPreferredSize(new Dimension(0, 100));
        actionPanel.setBackground(Color.WHITE);
        actionPanel.setBorder(BorderFactory.createTitledBorder("Actions"));
        add(actionPanel, BorderLayout.SOUTH);

        // Główny panel planszy - otrzymuje referencję do Game, aby czytać stan rozgrywki
        boardPanel = new BoardPanel(this);
        boardPanel.setPreferredSize(new Dimension(Config.GRID_SIZE * Config.CELL_SIZE, Config.GRID_SIZE * Config.CELL_SIZE));
        JScrollPane scrollPane = new JScrollPane(boardPanel);
        scrollPane.getVerticalScrollBar().setUnitIncrement(16);
        add(scrollPane, BorderLayout.CENTER);

        // Ustawia początkowy widok planszy w lewym górnym rogu
        SwingUtilities.invokeLater(() -> scrollPane.getViewport().setViewPosition(new Point(0, 0)));

        // Finalizacja rozmiaru i położenia okna
        pack();
        setSize(1200, 800);
        setLocationRelativeTo(null);
    }

    /**
     * Tworzy początkowy zestaw tokenów i ustawia ich stan startowy.
     *
     * Przy pierwszym uruchomieniu zapisuje dane do MongoDB.
     * Przy kolejnych uruchomieniach odczytuje już zapisany stan.
     */
    private void initTokens() {
        tokens = new ArrayList<>();
        Random rand = new Random();

        // --- WARRIOR ---
        // Bohater walczący wręcz - ma wysoki HP i kilka prostych akcji ofensywnych/defensywnych
        Token warrior = new Token("Warrior", 200, 10, 10, Color.RED);
        warrior.actions.add(new Action("Strike", ActionType.SINGLE, 1, 60, false, 0));
        warrior.actions.add(new Action("Big Strike", ActionType.SELF_AREA, 0, 40, false, 1));
        warrior.actions.add(new Action("Shield", ActionType.SELF, 0, 0, false, 0));
        warrior.actions.add(new Action("Trip", ActionType.SINGLE, 1, 0, false, 0));

        // --- MAGE ---
        // Postać dystansowa / wspierająca - niższe HP, ale silniejsze akcje specjalne
        Token mage = new Token("Mage", 50, 12, 10, Color.BLUE);
        mage.actions.add(new Action("Fireball", ActionType.AREA, 10, 50, false, 3)); 
        mage.actions.add(new Action("Heal", ActionType.ALLY, 10, -50, true, 0));
        mage.actions.add(new Action("Spark", ActionType.SINGLE, 40, 70, false, 0));

        tokens.add(warrior);
        tokens.add(mage);

        // --- GOBLINS ---
        // Trzech przeciwników sterowanych przez grę; każdy ma własną nazwę i pozycję startową
        String[] gobNames = {"goblin1", "goblin2", "goblin3"};
        for (int i = 0; i < 3; i++) {
            Token gob = new Token(gobNames[i], 100, 14 + i * 2, 10, new Color(0, 150, 0));
            gob.actions.add(new Action("Strike", ActionType.SINGLE, 1, 40, false, 0));
            gob.actions.add(new Action("Arrow", ActionType.SINGLE, 50, 20, false, 0));
            tokens.add(gob);
        }

        // Obsługa stanu początkowego tokenów z MongoDB
        Database db = Database.getInstance();
        boolean hasTokens = db.hasInitialTokens();

        for (Token t : tokens) {
            if (!hasTokens) {
                // Pierwsze uruchomienie - zapisujemy początkowy stan do bazy
                db.saveInitialToken(t);
            } else {
                // Kolejne uruchomienia - wczytujemy istniejący stan początkowy
                db.applyInitialTokenData(t);
            }
            // Inicjatywa jest losowana dla każdego tokena przy starcie rundy
            t.initiative = rand.nextInt(20) + 1;
        }
        // Sortowanie od najwyższej inicjatywy do najniższej
        tokens.sort((t1, t2) -> Integer.compare(t2.initiative, t1.initiative));
    }

    /**
     * Kończy bieżącą turę i przekazuje kolejkę następnemu tokenowi.
     *
     * Dodatkowo:
     * - aktualizuje licznik rund
     * - resetuje stan ruchu i użycia akcji dla nowego aktywnego tokena
     * - czyści zaznaczenia i odświeża UI
     */
    private void endTurn() {
        if (!tokens.isEmpty()) {
            // Przesunięcie tokena z początku listy na koniec oznacza zmianę tury
            Token current = tokens.remove(0);
            tokens.add(current);
            
            turnsTakenThisRound++;
            if (turnsTakenThisRound >= tokens.size()) {
                turnsTakenThisRound = 0;
                currentRound++;
                initiativePanel.setBorder(BorderFactory.createTitledBorder("Initiative - Turn " + currentRound));
            }
            
            // Efekt potknięcia trwa tylko jedną turę
            current.tripped = false;
            
            // Nowy aktywny token dostaje pełny ruch i odzyskuje możliwość akcji
            Token newCurrent = tokens.get(0);
            newCurrent.movementLeft = newCurrent.maxMovement;
            newCurrent.actionUsed = false;
             
            // Odświeżenie wszystkich elementów interfejsu
            updateInitiativeList();
            selectedToken = null;
            selectedAction = null;
            validMoves.clear();
            validActionRange.clear();
            updateActionPanel();
            boardPanel.repaint();
        }
    }

    /**
     * Odbudowuje widok listy inicjatywy na podstawie aktualnej kolejki tokenów.
     */
    private void updateInitiativeList() {
        listModel.clear();
        for (Token t : tokens) {
            listModel.addElement(t);
        }
    }

    /**
     * Aktualizuje panel akcji w zależności od tego, jaki token jest aktualnie zaznaczony.
     *
     * Pokazuje przyciski tylko wtedy, gdy zaznaczony token jest aktywny i nie zużył jeszcze akcji.
     */
    void updateActionPanel() {
        actionPanel.removeAll();
        // Akcje są dostępne tylko dla aktywnego tokena w kolejce
        if (selectedToken != null && !selectedToken.actionUsed && !tokens.isEmpty() && selectedToken == tokens.get(0)) {
            for (Action a : selectedToken.actions) {
                JButton btn = new JButton(a.name);
                btn.addActionListener(e -> {
                    // Ustawia wybraną akcję i wylicza jej zasięg
                    selectedAction = a;
                    calculateActionRange(selectedToken, a); 
                    boardPanel.repaint();
                });
                actionPanel.add(btn);
            }
        }
        actionPanel.revalidate();
        actionPanel.repaint();
    }
    
    /**
     * Wykonuje wybraną akcję na celu lub w punkcie docelowym.
     *
     * Obsługuje:
     * - Shield
     * - ataki pojedyncze
     * - leczenie
     * - obszarowe obrażenia
     */
    void executeAction(Token actor, Token target, Point targetPoint) {
        // Shield jest obsługiwany osobno, bo nie zadaje obrażeń ani nie wymaga targetu
        if (selectedAction.name.equals("Shield")) {
            actor.shield += 30;
            finishActionUse(actor);
            return;
        }

        // Akcje SINGLE i ALLY działają na jeden token
        if (selectedAction.type == ActionType.SINGLE || selectedAction.type == ActionType.ALLY) {
            if (target != null) {
                if (selectedAction.name.equals("Trip")) {
                    target.tripped = true;
                } else if (selectedAction.isHeal) {
                    // Leczenie nie może przekroczyć maksymalnego HP
                    target.hp = Math.min(target.hp + (-selectedAction.damage), target.maxHp);
                } else {
                    // Standardowe zadanie obrażeń
                    takeDamage(target, selectedAction.damage);
                }
            }
        } 
        // Akcje obszarowe przeliczają obrażenia dla wszystkich tokenów w zasięgu AOE
        else if (selectedAction.type == ActionType.AREA || selectedAction.type == ActionType.SELF_AREA) {
            int r = selectedAction.aoeRadius;
            for (Token t : tokens) {
                if (t.hp > 0 && Math.abs(t.x - targetPoint.x) <= r && Math.abs(t.y - targetPoint.y) <= r) {
                    // SELF_AREA nie powinno ranić samego wykonawcy
                    if (selectedAction.type == ActionType.SELF_AREA && t == actor) continue; 
                    takeDamage(t, selectedAction.damage);
                }
            }
        }
        
        finishActionUse(actor);
    }
    
    /**
     * Kończy użycie akcji przez token i usuwa martwe jednostki z kolejki.
     *
     * Dodatkowo koryguje licznik tur w rundzie, jeśli usunięty token był już przetworzony.
     */
    private void finishActionUse(Token actor) {
        actor.actionUsed = true;
        
        // Usuwanie martwych tokenów z listy aktywnych jednostek
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens.get(i).hp <= 0) {
                if (i < turnsTakenThisRound) {
                    // Jeśli usunięto token wcześniej uwzględniony w tej rundzie, koryguj licznik
                    turnsTakenThisRound--; 
                }
                tokens.remove(i);
                i--;
            }
        }
        updateInitiativeList();
    }

    /**
     * Zadaje obrażenia tokenowi, uwzględniając aktywną tarczę.
     *
     * Tarczę można traktować jako bufor pochłaniający część obrażeń.
     */
    private void takeDamage(Token t, int dmg) {
        // Tarcza absorbuje część lub całość obrażeń
        if (t.shield > 0) {
            int absorbed = Math.min(dmg, t.shield);
            dmg -= absorbed;
            t.shield -= absorbed; 
            if(t.shield < 30) t.shield = 0; 
        }
        // Niewchłonięte obrażenia obniżają HP
        t.hp -= dmg;
    }

    /**
     * Wyznacza wszystkie pola dostępne dla akcji danego tokena.
     *
     * Dla akcji SELF i SELF_AREA zwraca tylko pole obecnej pozycji tokena.
     * Dla pozostałych akcji wylicza zasięg na podstawie wartości range.
     */
    private void calculateActionRange(Token t, Action a) {
        validActionRange.clear();
        
        if (a.type == ActionType.SELF || a.type == ActionType.SELF_AREA) {
            // Akcja używana na sobie samym
            validActionRange.add(new Point(t.x, t.y));
            return;
        }
        
        // Budowanie kwadratowego zasięgu wokół tokena, ograniczonego do planszy
        int range = a.range;
        for (int i = -range; i <= range; i++) {
            for (int j = -range; j <= range; j++) {
                if (Math.max(Math.abs(i), Math.abs(j)) <= range) {
                    int nx = t.x + i;
                    int ny = t.y + j;
                    if (nx >= 0 && nx < Config.GRID_SIZE && ny >= 0 && ny < Config.GRID_SIZE) {
                        validActionRange.add(new Point(nx, ny));
                    }
                }
            }
        }
    }

    /**
     * Zwraca token znajdujący się na zadanych współrzędnych siatki.
     *
     * Jeśli pole jest puste, zwraca null.
     */
    Token getTokenAt(int x, int y) {
        return tokens.stream().filter(t -> t.hp > 0 && t.x == x && t.y == y).findFirst().orElse(null);
    }

    /**
     * Oblicza dostępne pola ruchu dla tokena, z uwzględnieniem kosztu ruchu,
     * przeszkód na planszy i pozostałych punktów ruchu.
     */
    void calculateValidMoves(Token t) {
        validMoves.clear();
        // Priorytetowa kolejka przechowuje pola do przetworzenia w kolejności najniższego kosztu
        PriorityQueue<PathNode> openSet = new PriorityQueue<>(Comparator.comparingInt(n -> n.cost));
        Map<Point, Integer> costs = new HashMap<>();

        Point start = new Point(t.x, t.y);
        openSet.add(new PathNode(start, 0));
        costs.put(start, 0);

        // Maksymalny koszt ruchu równy pozostałemu movement tokena
        int maxCost = t.movementLeft;
        // Osiem kierunków ruchu: pion, poziom i skosy
        int[] dx = {-1, 0, 1, -1, 1, -1, 0, 1}; 
        int[] dy = {-1, -1, -1, 0, 0, 1, 1, 1};

        while (!openSet.isEmpty()) {
            PathNode current = openSet.poll();
            if (current.cost > costs.getOrDefault(current.p, Integer.MAX_VALUE)) continue;

            // Aktualne pole jest osiągalne przy danym koszcie
            validMoves.put(current.p, current.cost);

            // Sprawdź wszystkich sąsiadów bieżącego pola
            for (int i = 0; i < 8; i++) {
                int nx = current.p.x + dx[i];
                int ny = current.p.y + dy[i];

                if (nx >= 0 && nx < Config.GRID_SIZE && ny >= 0 && ny < Config.GRID_SIZE) {
                    // Ruch po skosie kosztuje więcej niż ruch prosty
                    int moveCost = (dx[i] != 0 && dy[i] != 0) ? 2 : 1;
                    int newCost = current.cost + moveCost;
                    Point neighbor = new Point(nx, ny);
                    // Pole jest zajęte, jeśli stoi tam żywy token inny niż aktualnie poruszany
                    boolean occupied = tokens.stream().anyMatch(tok -> tok.hp > 0 && tok != t && tok.x == nx && tok.y == ny);

                    if (newCost <= maxCost && !occupied) {
                        if (newCost < costs.getOrDefault(neighbor, Integer.MAX_VALUE)) {
                            costs.put(neighbor, newCost);
                            openSet.add(new PathNode(neighbor, newCost));
                        }
                    }
                }
            }
        }
    }

    /**
     * Punkt wejścia aplikacji.
     * Tworzy okno gry i ustawia je jako widoczne na EDT Swinga.
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Game().setVisible(true));
    }
}
