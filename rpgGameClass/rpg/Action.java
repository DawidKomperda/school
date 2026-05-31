package rpg;

/**
 * Represents a combat capability that a Token can use on their turn.
 * It encapsulates the type, range, amount of damage/healing, and area of effect.
 */
public class Action {
    public String name;
    public ActionType type;
    public int range;
    public int damage;
    public boolean isHeal;
    public int aoeRadius;

    /**
     * Constructs a new Action.
     *
     * @param name      The display name of the action.
     * @param type      The targeting behavior of the action.
     * @param range     The maximum distance in squares this action can reach.
     * @param damage    The flat amount of damage (or healing if negative and isHeal is true).
     * @param isHeal    Whether or not this action restores HP.
     * @param aoeRadius The radius of effect for AREA and SELF_AREA actions.
     */
    public Action(String name, ActionType type, int range, int damage, boolean isHeal, int aoeRadius) {
        this.name = name;
        this.type = type;
        this.range = range;
        this.damage = damage;
        this.isHeal = isHeal;
        this.aoeRadius = aoeRadius;
    }
}
