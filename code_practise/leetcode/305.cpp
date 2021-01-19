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
    int x, y, d;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    unordered_map<int, unordered_map<int, int>> visited;
    
    void run(Robot& robot) {
        visited[x][y] = 1;
        robot.clean();
        
        int curx = x; int cury = y;
        for (int i = 0; i < 4; ++i) {
            int nx = curx + dx[d%4];
            int ny = cury + dy[d%4];
            if (!visited[nx][ny] && robot.move()) {
                x = nx; y = ny;
                run(robot);
                // now we are at (nx, ny), go back to (x, y)
                robot.turnRight(); robot.turnRight();
                assert(robot.move());
                robot.turnRight(); robot.turnRight();
            }
            
            d++;
            robot.turnRight();
        }
    }
public:
    void cleanRoom(Robot& robot) {
        x = 0; y = 0; d = 0;        
        run(robot);
    }
};
