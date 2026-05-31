package rpg;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * Component Class handling rendering the visual representation of tokens on the 2D grid space,
 * registering mouse interaction clicks for selection mechanics, and drawing action highlights.
 * 
 * Odpowiedzialny za:
 * - Renderowanie siatki i wszystkich tokenów na planszy
 * - Obsługę interakcji myszą (klikanie, najechanie)
 * - Rysowanie dostępnych ruchów i zasięgów akcji
 * - Wyświetlanie statystyk tokenów (HP, movement, imiona)
 */
public class BoardPanel extends JPanel {
    // Referencja do głównej klasy Game - dostęp do stanu gry i tokenów
    private Game game;

    /**
     * Konstruktor inicjalizujący panel i rejestrujący nasłuchiwacze myszy.
     * Ustawia up nasłuchiwacze dla zdarzeń myszy: klikanie i ruch.
     * 
     * @param game Referencja do głównej klasy Game - potrzebna do dostępu do danych gry
     */
    public BoardPanel(Game game) {
        this.game = game;
        
        // Nasłuchiwacz kliknięć muszą - obsługuje wybór tokenów i akcji
        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                handleMouseClick(e.getX(), e.getY());
            }
        });
        
        // Nasłuchiwacz ruchu myszy - śledzi pozycję kursora na siatce dla podglądów
        addMouseMotionListener(new MouseAdapter() {
            @Override
            public void mouseMoved(MouseEvent e) {
                // Konwertuje współrzędne pikseli na współrzędne siatki
                game.hoverGrid.x = e.getX() / Config.CELL_SIZE;
                game.hoverGrid.y = e.getY() / Config.CELL_SIZE;
                repaint(); // Odświeża panel aby pokazać aktualne podglądy
            }
        });
    }

    /**
     * Obsługuje zdarzenie kliknięcia muszą na planszy.
     * Obsługuje trzy główne scenariusze:
     * 1. Wykonanie wybranej akcji w punkcie docelowym
     * 2. Wybranie tokena do kontroli
     * 3. Ruch wybranego tokena na dostępne pole
     * 
     * @param mouseX Współrzędna X kliknięcia w pikselach
     * @param mouseY Współrzędna Y kliknięcia w pikselach
     */
    private void handleMouseClick(int mouseX, int mouseY) {
        // Konwertuje współrzędne pikseli na współrzędne siatki
        int gridX = mouseX / Config.CELL_SIZE;
        int gridY = mouseY / Config.CELL_SIZE;
        Point targetPoint = new Point(gridX, gridY);

        // Sprawdza, czy w danym punkcie znajduje się token
        Token clickedToken = game.getTokenAt(gridX, gridY);

        // SCENARIUSZ 1: Akcja została wybrana - obsługuj wykonanie akcji
        if (game.selectedAction != null && game.selectedToken != null) {
            boolean execute = false;
            
            // Jeśli akcja jest na siebie lub na siebie z AOE, punkt docelowy to pozycja tokena
            if (game.selectedAction.type == ActionType.SELF || game.selectedAction.type == ActionType.SELF_AREA) {
                targetPoint = new Point(game.selectedToken.x, game.selectedToken.y);
                execute = true;
            } 
            // Jeśli akcja wymaga zasięgu, sprawdź czy punkt jest w validActionRange
            else if (game.validActionRange.contains(targetPoint)) {
                execute = true;
            }

            // Jeśli można wykonać akcję, pokaż potwierdzenie i wykonaj ją
            if (execute) {
                int confirm = JOptionPane.showConfirmDialog(this, 
                        "Are you sure you want to perform: " + game.selectedAction.name + "?", 
                        "Confirm Action", JOptionPane.YES_NO_OPTION);
                if (confirm == JOptionPane.YES_OPTION) {
                    game.executeAction(game.selectedToken, clickedToken, targetPoint);
                }
            }
            
            // Wyczyść wybrane akcje i zaznaczenia
            game.selectedAction = null;
            game.validActionRange.clear();
            repaint();
            return;
        }

        // SCENARIUSZ 2: Kliknięto na token - wybierz go
        if (clickedToken != null) {
            game.selectedToken = clickedToken;
            game.updateActionPanel();
            // Jeśli to token gracza (index 0), nie jest potknięty i ma movement - oblicz dostępne ruchy
            if (clickedToken == game.tokens.get(0) && !clickedToken.tripped && clickedToken.movementLeft > 0) {
                game.calculateValidMoves(game.selectedToken);
            } else {
                game.validMoves.clear();
            }
        } 
        // SCENARIUSZ 3: Ruch wybranego tokena na dostępne pole
        else if (game.selectedToken != null && game.validMoves.containsKey(targetPoint)) {
            // Upewnij się, że pole docelowe jest puste (brak tokena)
            if (game.getTokenAt(gridX, gridY) == null) {
                // Odejmij koszt movement z dostępnych punktów
                game.selectedToken.movementLeft -= game.validMoves.get(targetPoint);
                // Przesuń token na nową pozycję
                game.selectedToken.x = gridX;
                game.selectedToken.y = gridY;
                // Usuń zaznaczenie po ruchu
                game.selectedToken = null;
                game.updateActionPanel();
                game.validMoves.clear();
            }
        } 
        // Jeśli nic nie pasuje - wyczyść zaznaczenia
        else {
            game.selectedToken = null;
            game.updateActionPanel();
            game.validMoves.clear();
            game.validActionRange.clear();
        }
        repaint(); // Odśwież planszę po każdej akcji
    }

    /**
     * Rysuje całą zawartość panelu: siatkę, tokeny, zaznaczenia i statystyki.
     * Wykonywany za każdym razem gdy repaint() jest wywoływany.
     * Optymalizuje rysowanie tylko widocznej części panelu.
     * 
     * @param g Kontekst graficzny do rysowania
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        // Pobierz obszar który wymaga odświeżenia
        Rectangle clip = g.getClipBounds();

        // Oblicz zakresy siatki które trzeba narysować (optymalizacja)
        int startX = Math.max(0, clip.x / Config.CELL_SIZE);
        int startY = Math.max(0, clip.y / Config.CELL_SIZE);
        int endX = Math.min(Config.GRID_SIZE, (clip.x + clip.width) / Config.CELL_SIZE + 1);
        int endY = Math.min(Config.GRID_SIZE, (clip.y + clip.height) / Config.CELL_SIZE + 1);

        // RYSOWANIE: Zaznaczenia akcji i zasięgów
        if (game.selectedAction != null) {
            // Jeśli akcja to samo-Area - rysuj AOE wokół wybranego tokena (czerwone pole)
            if (game.selectedAction.type == ActionType.SELF_AREA) {
                g.setColor(new Color(255, 100, 100, 150)); // Czerwony, półprzezroczysty
                int r = game.selectedAction.aoeRadius;
                for (int dx = -r; dx <= r; dx++) {
                    for (int dy = -r; dy <= r; dy++) {
                        g.fillRect((game.selectedToken.x + dx) * Config.CELL_SIZE, (game.selectedToken.y + dy) * Config.CELL_SIZE, Config.CELL_SIZE, Config.CELL_SIZE);
                    }
                }
            } 
            // Dla innych akcji - rysuj dostępny zasięg (zielone pole)
            else {
                g.setColor(new Color(144, 238, 144, 150)); // Jasny zielony
                for (Point p : game.validActionRange) {
                    if (p.x >= startX && p.x < endX && p.y >= startY && p.y < endY) {
                        g.fillRect(p.x * Config.CELL_SIZE, p.y * Config.CELL_SIZE, Config.CELL_SIZE, Config.CELL_SIZE);
                    }
                }
                
                // Jeśli to akcja Area - pokaż podgląd AOE przy myszce (czerwone pole)
                if (game.selectedAction.type == ActionType.AREA && game.validActionRange.contains(game.hoverGrid)) {
                    g.setColor(new Color(255, 100, 100, 150)); // Czerwony, półprzezroczysty
                    int r = game.selectedAction.aoeRadius;
                    for (int dx = -r; dx <= r; dx++) {
                        for (int dy = -r; dy <= r; dy++) {
                            g.fillRect((game.hoverGrid.x + dx) * Config.CELL_SIZE, (game.hoverGrid.y + dy) * Config.CELL_SIZE, Config.CELL_SIZE, Config.CELL_SIZE);
                        }
                    }
                }
            }
        } 
        // Jeśli akcja nie jest wybrana - rysuj dostępne ruchy (niebieskie pole)
        else {
            // Rysuj dostępne pola do ruchu (jasny niebieski)
            g.setColor(new Color(173, 216, 230, 150));
            for (Point p : game.validMoves.keySet()) {
                if (p.x >= startX && p.x < endX && p.y >= startY && p.y < endY) {
                    g.fillRect(p.x * Config.CELL_SIZE, p.y * Config.CELL_SIZE, Config.CELL_SIZE, Config.CELL_SIZE);
                }
            }
        }

        // RYSOWANIE: Siatka
        g.setColor(Color.LIGHT_GRAY);
        // Rysuj linie pionowe siatki
        for (int x = startX; x <= endX; x++) {
            g.drawLine(x * Config.CELL_SIZE, clip.y, x * Config.CELL_SIZE, clip.y + clip.height);
        }
        // Rysuj linie poziome siatki
        for (int y = startY; y <= endY; y++) {
            g.drawLine(clip.x, y * Config.CELL_SIZE, clip.x + clip.width, y * Config.CELL_SIZE);
        }

        // RYSOWANIE: Zaznaczenie tokena przy myszce jeśli akcja jest dostępna
        Token hoveredToken = game.getTokenAt(game.hoverGrid.x, game.hoverGrid.y);
        // Jeśli token jest pod myszą i akcja jest wybrana oraz w zasięgu - podświetl go
        if (hoveredToken != null && game.selectedAction != null) {
            if (game.validActionRange.contains(new Point(hoveredToken.x, hoveredToken.y))) {
                g.setColor(Color.RED); // Czerwona obwódka
                g.drawRect(hoveredToken.x * Config.CELL_SIZE, hoveredToken.y * Config.CELL_SIZE, Config.CELL_SIZE, Config.CELL_SIZE);
            }
        }

        // RYSOWANIE: Tokeny i ich statystyki
        for (Token t : game.tokens) {
            // Pomiń tokeny które są martwe (HP <= 0)
            if (t.hp <= 0) continue; 
            
            // Rysuj tylko tokeny w widocznym obszarze
            if (t.x >= startX && t.x < endX && t.y >= startY && t.y < endY) {
                // Rysuj token jako koło w jego kolorze
                g.setColor(t.color);
                g.fillOval(t.x * Config.CELL_SIZE + 2, t.y * Config.CELL_SIZE + 4, Config.CELL_SIZE - 4, Config.CELL_SIZE - 4);
                
                // Jeśli token jest wybrany - rysuj żółtą obwódkę (dwie warstwy dla lepszej widoczności)
                if (t == game.selectedToken) {
                    g.setColor(Color.YELLOW);
                    g.drawOval(t.x * Config.CELL_SIZE + 2, t.y * Config.CELL_SIZE + 4, Config.CELL_SIZE - 4, Config.CELL_SIZE - 4);
                    g.drawOval(t.x * Config.CELL_SIZE + 1, t.y * Config.CELL_SIZE + 3, Config.CELL_SIZE - 2, Config.CELL_SIZE - 2);
                }
                
                // Rysuj pasek HP na górze tokena
                int barHeight = 4;
                int barTop = t.y * Config.CELL_SIZE;
                // Tło paska HP (czarne)
                g.setColor(Color.BLACK);
                g.fillRect(t.x * Config.CELL_SIZE, barTop, Config.CELL_SIZE, barHeight);
                // Oblicz i narysuj zielony pasek HP na podstawie obecnego HP
                double hpPercent = Math.max(0.0, (double) t.hp / t.maxHp);
                int hpWidth = (int) (hpPercent * Config.CELL_SIZE);
                g.setColor(Color.GREEN);
                g.fillRect(t.x * Config.CELL_SIZE, barTop, hpWidth, barHeight);
                
                // Jeśli token ma shield - dodaj cyan obwódkę paska HP
                if (t.shield > 0) {
                    g.setColor(Color.CYAN);
                    g.drawRect(t.x * Config.CELL_SIZE, barTop, Config.CELL_SIZE, barHeight);
                }
                
                // Rysuj tekst Movement/MaxMovement nad tokenem
                g.setFont(new Font("Arial", Font.BOLD, 12));
                String movStr = t.movementLeft + "/" + t.maxMovement;
                int textX = t.x * Config.CELL_SIZE;
                int textYTop = t.y * Config.CELL_SIZE - 2;
                
                // Rysuj tekst Movement z czarnym outlinem dla czytelności
                g.setColor(Color.BLACK);
                g.drawString(movStr, textX - 1, textYTop - 1);
                g.drawString(movStr, textX + 1, textYTop - 1);
                g.drawString(movStr, textX - 1, textYTop + 1);
                g.drawString(movStr, textX + 1, textYTop + 1);
                // Główny tekst w bieli
                g.setColor(Color.WHITE);
                g.drawString(movStr, textX, textYTop);
                
                // Rysuj imię tokena poniżej
                FontMetrics fm = g.getFontMetrics();
                int nameWidth = fm.stringWidth(t.name);
                int nameX = t.x * Config.CELL_SIZE + (Config.CELL_SIZE - nameWidth) / 2; // Wyśrodkuj imię
                int nameYBottom = t.y * Config.CELL_SIZE + Config.CELL_SIZE + 12;

                // Rysuj imię z czarnym outlinem dla czytelności
                g.setColor(Color.BLACK);
                g.drawString(t.name, nameX - 1, nameYBottom - 1);
                g.drawString(t.name, nameX + 1, nameYBottom - 1);
                g.drawString(t.name, nameX - 1, nameYBottom + 1);
                g.drawString(t.name, nameX + 1, nameYBottom + 1);
                // Główny tekst w bieli
                g.setColor(Color.WHITE);
                g.drawString(t.name, nameX, nameYBottom);
            }
        }
    }
}
