package rpg;

/**
 * Defines the targeting and area behavior of an Action.
 */
public enum ActionType {
    /** Target a single entity at a range. */
    SINGLE,
    
    /** Target a point in range, affecting everything around it. */
    AREA,
    
    /** Target an ally (including self) to heal. */
    ALLY,
    
    /** Apply a self-buff or effect directly to the caster. */
    SELF,
    
    /** Create an area of effect centered exclusively around the caster. */
    SELF_AREA
}
