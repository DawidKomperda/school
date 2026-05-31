package rpg;

import java.awt.Point;

/**
 * Struct tracking pathfinding step nodes
 */
public class PathNode {
    Point p; 
    int cost;
    public PathNode(Point p, int cost) { 
        this.p = p; 
        this.cost = cost; 
    }
}
