/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */
class Solution {
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    unordered_set<string> visited;
    void visit(int x, int y, int dir, Robot& r) {
        r.clean();
        auto rep = [](int xx, int yy) {
            return to_string(xx) + "$" + to_string(yy);
        };
        
        visited.insert(rep(x, y));
        for (int i = 0; i < 4; ++i) {
            int ndir = (i + dir) % 4;
            int nx = dx[ndir] + x;
            int ny = dy[ndir] + y;
            if (visited.count(rep(nx, ny)) == 0 && r.move()) {
                visit(nx, ny, ndir, r);
            }
            r.turnRight();
        }
        
        if (!(x == 0 && y == 0)) {
            r.turnRight(); r.turnRight();
            assert(r.move());
            r.turnRight(); r.turnRight();
        }
    }
public:
    void cleanRoom(Robot& robot) {
        visit(0, 0, 0, robot);
    }
};