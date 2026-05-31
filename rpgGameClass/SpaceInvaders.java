import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Iterator;
import javax.swing.*;

public class SpaceInvaders extends JPanel implements ActionListener, KeyListener {
    private Timer timer;
    private int playerX = 375;
    private final int playerY = 500;
    private int playerDx = 0;
    
    private ArrayList<Rectangle> bullets = new ArrayList<>();
    private ArrayList<Rectangle> aliens = new ArrayList<>();
    
    private int alienDirection = 2;
    private boolean alienMoveDown = false;
    private int score = 0;
    private boolean gameOver = false;
    private boolean won = false;

    public SpaceInvaders() {
        setFocusable(true);
        setBackground(Color.BLACK);
        addKeyListener(this);
        
        // Initialize alien grid
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 10; col++) {
                aliens.add(new Rectangle(50 + col * 50, 50 + row * 40, 30, 20));
            }
        }
        
        // 60 FPS timer
        timer = new Timer(16, this);
        timer.start();
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        
        if (gameOver) {
            g.setColor(won ? Color.GREEN : Color.RED);
            g.setFont(new Font("Arial", Font.BOLD, 40));
            String msg = won ? "YOU WIN!" : "GAME OVER";
            g.drawString(msg, 300, 300);
            return;
        }
        
        // Draw Player
        g.setColor(Color.GREEN);
        g.fillRect(playerX, playerY, 40, 20);
        g.fillRect(playerX + 15, playerY - 10, 10, 10); // Turret
        
        // Draw Bullets
        g.setColor(Color.WHITE);
        for (Rectangle b : bullets) {
            g.fillRect(b.x, b.y, b.width, b.height);
        }
        
        // Draw Aliens
        g.setColor(Color.RED);
        for (Rectangle a : aliens) {
            g.fillRect(a.x, a.y, a.width, a.height);
        }
        
        // Draw Score
        g.setColor(Color.WHITE);
        g.setFont(new Font("Arial", Font.BOLD, 20));
        g.drawString("Score: " + score, 10, 30);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (gameOver) return;
        
        // Move player
        playerX += playerDx;
        if (playerX < 0) playerX = 0;
        if (playerX > 740) playerX = 740; // Frame width - player width margin
        
        // Move bullets
        Iterator<Rectangle> it = bullets.iterator();
        while (it.hasNext()) {
            Rectangle b = it.next();
            b.y -= 7;
            if (b.y < 0) it.remove();
        }
        
        // Move aliens
        boolean hitEdge = false;
        for (Rectangle a : aliens) {
            if (alienMoveDown) {
                a.y += 20;
            } else {
                a.x += alienDirection;
                if (a.x < 10 || a.x > 750) {
                    hitEdge = true;
                }
            }
        }
        
        if (alienMoveDown) {
            alienMoveDown = false;
        } else if (hitEdge) {
            alienDirection = -alienDirection;
            alienMoveDown = true;
        }
        
        // Handle Collisions Checks
        Iterator<Rectangle> bIt = bullets.iterator();
        while (bIt.hasNext()) {
            Rectangle b = bIt.next();
            Iterator<Rectangle> aIt = aliens.iterator();
            boolean hit = false;
            while (aIt.hasNext()) {
                Rectangle a = aIt.next();
                if (b.intersects(a)) {
                    aIt.remove();
                    hit = true;
                    score += 10;
                    break;
                }
            }
            if (hit) bIt.remove();
        }
        
        // Win / Loss Condition
        for (Rectangle a : aliens) {
            if (a.y + a.height >= playerY) {
                gameOver = true;
            }
        }
        if (aliens.isEmpty()) {
            gameOver = true;
            won = true;
        }
        
        repaint();
    }

    @Override
    public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();
        if (key == KeyEvent.VK_LEFT || key == KeyEvent.VK_A) playerDx = -5;
        if (key == KeyEvent.VK_RIGHT || key == KeyEvent.VK_D) playerDx = 5;
        if (key == KeyEvent.VK_SPACE) {
            // Only allow max 3 bullets on screen at a time to prevent spam
            if (bullets.size() < 3) {
                bullets.add(new Rectangle(playerX + 18, playerY - 10, 4, 10));
            }
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
        int key = e.getKeyCode();
        if (key == KeyEvent.VK_LEFT || key == KeyEvent.VK_A) {
            if (playerDx < 0) playerDx = 0;
        }
        if (key == KeyEvent.VK_RIGHT || key == KeyEvent.VK_D) {
            if (playerDx > 0) playerDx = 0;
        }
    }

    @Override
    public void keyTyped(KeyEvent e) {}

    public static void main(String[] args) {
        JFrame frame = new JFrame("Space Invaders");
        SpaceInvaders game = new SpaceInvaders();
        frame.add(game);
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}