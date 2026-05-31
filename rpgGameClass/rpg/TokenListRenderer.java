package rpg;

import javax.swing.*;
import java.awt.*;

/**
 * Styles the Initiative JList components dynamically to bold the top user,
 * modify the HP strings, and reflect statuses visually to players.
 */
public class TokenListRenderer extends DefaultListCellRenderer {
    @Override
    public Component getListCellRendererComponent(JList<?> list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
        Component c = super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
        if (value instanceof Token) {
            Token t = (Token) value;
            setText(t.name + " (" + t.initiative + ") - " + t.hp + " HP" + (t.tripped ? " [TRIPPED]" : ""));
            setForeground(t.hp <= 0 ? Color.GRAY : t.color);
            
            if (index == 0) { 
                setFont(getFont().deriveFont(Font.BOLD)); 
                setBackground(new Color(230, 230, 250)); 
            } else { 
                setFont(getFont().deriveFont(Font.PLAIN)); 
                setBackground(Color.WHITE); 
            }
        }
        return c;
    }
}
