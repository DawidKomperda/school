package rpg;

import java.awt.Color;
import java.util.ArrayList;
import java.util.List;

/**
 * Represents a discrete character, monster, or player on the game board.
 * Tracks health, current position, movement limits, active status effects, and abilities.
 */
public class Token {
    public String name;
    public int maxHp, hp;
    public int x, y;
    
    // Combat initiative roll
    public int initiative;
    
    // Graphical representation color
    public Color color;
    
    // Abilities the token can use
    public List<Action> actions = new ArrayList<>();
    
    // Status effects
    public boolean tripped = false;
    public int shield = 0;
    
    // Turn restrictions
    public int maxMovement = 10;
    public int movementLeft = 10;
    public boolean actionUsed = false;

    /**
     * Initializes a new Token with base statistics.
     *
     * @param name   The string identifier of the character.
     * @param maxHp  The maximal health capacity.
     * @param x      The initial grid X coordinate.
     * @param y      The initial grid Y coordinate.
     * @param color  The core color used to draw the token on the board.
     */
    public Token(String name, int maxHp, int x, int y, Color color) {
        this.name = name;
        this.maxHp = maxHp;
        this.hp = maxHp;
        this.x = x;
        this.y = y;
        this.color = color;
    }

    @Override
    public String toString() {
        return name + " (Init: " + initiative + ") HP: " + hp + "/" + maxHp;
    }
}
