/*
 * lc submit 749.cpp
 *   ✔ Accepted
 *   ✔ 32/32 cases passed (123 ms)
 *   ✔ Your runtime beats 6.84 % of cpp submissions
 *
 * [750] Contain Virus
 *
 * https://leetcode.com/problems/contain-virus/description/
 *
 * algorithms
 * Hard (38.91%)
 * Total Accepted:    1.2K
 * Total Submissions: 3.1K
 * Testcase Example:  '[[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]]'
 *
 * 
 * A virus is spreading rapidly, and your task is to quarantine the infected
 * area by installing walls.
 * 
 * The world is modeled as a 2-D array of cells, where 0 represents uninfected
 * cells, and 1 represents cells contaminated with the virus.  A wall (and only
 * one wall) can be installed between any two 4-directionally adjacent cells,
 * on the shared boundary.
 * 
 * Every night, the virus spreads to all neighboring cells in all four
 * directions unless blocked by a wall.
 * Resources are limited. Each day, you can install walls around only one
 * region -- the affected area (continuous block of infected cells) that
 * threatens the most uninfected cells the following night. There will never be
 * a tie.
 * 
 * Can you save the day? If so, what is the number of walls required? If not,
 * and the world becomes fully infected, return the number of walls used.
 * 
 * 
 * Example 1:
 * 
 * Input: grid = 
 * [[0,1,0,0,0,0,0,1],
 * ⁠[0,1,0,0,0,0,0,1],
 * ⁠[0,0,0,0,0,0,0,1],
 * ⁠[0,0,0,0,0,0,0,0]]
 * Output: 10
 * Explanation:
 * There are 2 contaminated regions.
 * On the first day, add 5 walls to quarantine the viral region on the left.
 * The board after the virus spreads is:
 * 
 * [[0,1,0,0,0,0,1,1],
 * ⁠[0,1,0,0,0,0,1,1],
 * ⁠[0,0,0,0,0,0,1,1],
 * ⁠[0,0,0,0,0,0,0,1]]
 * 
 * On the second day, add 5 walls to quarantine the viral region on the right.
 * The virus is fully contained.
 * 
 * 
 * 
 * Example 2:
 * 
 * Input: grid = 
 * [[1,1,1],
 * ⁠[1,0,1],
 * ⁠[1,1,1]]
 * Output: 4
 * Explanation: Even though there is only one cell saved, there are 4 walls
 * built.
 * Notice that walls are only built on the shared boundary of two different
 * cells.
 * 
 * 
 * 
 * Example 3:
 * 
 * Input: grid = 
 * [[1,1,1,0,0,0,0,0,0],
 * ⁠[1,0,1,0,1,1,1,1,1],
 * ⁠[1,1,1,0,0,0,0,0,0]]
 * Output: 13
 * Explanation: The region on the left only builds two new walls.
 * 
 * 
 * 
 * Note:
 * 
 * The number of rows and columns of grid will each be in the range [1, 50].
 * Each grid[i][j] will be either 0 or 1.
 * Throughout the described process, there is always a contiguous viral region
 * that will infect strictly more uncontaminated squares in the next round.
 * 
 * 
 */
class Solution {
   int n, m;
   vector<vector<int>> g;
   vector<vector<bool>> visited;;

   int ph(int x, int y) {
      return x + 100 * y;
   }

   bool isWhite(int x, int y) {
      if (x < 0 || x >= n) return false;
      if (y < 0 || y >= m) return false;
      if (visited[x][y]) return false;
      return g[x][y] == 0;
   }

   bool valid(int x, int y) {
      if (x < 0 || x >= n) return false;
      if (y < 0 || y >= m) return false;
      if (visited[x][y]) return false;
      return g[x][y] == 1;
   }

   int dx[4] = {0, 1, 0, -1};
   int dy[4] = {1, 0, -1, 0};

   pair<int, int> count(int x, int y) {
      int walls = 0;
      deque<pair<int, int>> q;
      unordered_set<int> p;
      visited = vector<vector<bool>>(n, vector<bool>(m, false));

      int ox = x, oy = y;
      q.push_back({x, y});
      visited[x][y] = true;
      while (!q.empty()) {
         auto top = q.front();
         q.pop_front();
         for (int i = 0; i < 4; ++i) {
            int x = top.first + dx[i];
            int y = top.second + dy[i];
            if (isWhite(x, y)) {
               walls++;
               p.insert(ph(x, y));
            } else if (valid(x, y)) {
               q.push_back({x, y});
               visited[x][y] = true;
            }
         }
      }

      return make_pair(walls, p.size());
   }

   int contain(int x, int y) {
      int count = 0;
      deque<pair<int, int>> q;
      visited = vector<vector<bool>>(n, vector<bool>(m, false));

      q.push_back({x, y});
      visited[x][y] = true;
      g[x][y] = 2;

      while (!q.empty()) {
         auto top = q.front();
         q.pop_front();
         count++;
         for (int i = 0; i < 4; ++i) {
            int x = top.first + dx[i];
            int y = top.second + dy[i];
            if (valid(x, y)) {
               g[x][y] = 2;
               visited[x][y] = true;
               q.push_back({x, y});
            }
         }
      }

      return count;
   }
public:
    int containVirus(vector<vector<int>>& grid) {
       std::swap(g, grid);
       n = g.size();
       if (n == 0) return 0;
       m = g[0].size();
       visited = vector<vector<bool>>(n, vector<bool>(m, false));
       int ret = 0;

       while (true) {
          // find largest:
          int best = -1, bx = 0, by = 0, walls = -1;
          visited = vector<vector<bool>>(n, vector<bool>(m, false));
          for (int x = 0; x < n; ++x) { for (int y = 0; y < m; ++y) {
             if (valid(x, y)) {
                auto t = count(x, y);
                if (t.second > best) {
                   best = t.second; bx = x; by = y; walls = t.first;
                }
             }
          }}

          if (best == -1) break;

          // contain them:
          //cout << "ret before = " << ret << endl;
          ret += walls;
          //cout << "ret=" << ret << "infection:" << best << endl;
          int total = contain(bx, by);

          // spread:
          visited = vector<vector<bool>>(n, vector<bool>(m, false));
          for (int x = 0; x < n; ++x) { for (int y = 0; y < m; ++y) {
             if (valid(x, y)) {
                deque<pair<int, int>> q;
                q.push_back({x, y});
                visited[x][y] = true;
                while(!q.empty()) {
                   auto top = q.front();
                   q.pop_front();
                   //cout << "!" << top.first << " " << top.second << endl;
                   total++;

                   for (int i = 0; i < 4; ++i) {
                      int x = top.first + dx[i];
                      int y = top.second + dy[i];
                      if (isWhite(x, y)) {
                         g[x][y] = 1;
                         visited[x][y] = true;
                         total++;
                      } else if (valid(x, y)) {
                         visited[x][y] = true;
                         q.push_back({x, y});
                      }
                   }
                }
             }
          }}

          //cout << "new total:" << total << endl;
          if (total == n * m) break;
       }

       return ret;
    }
};

/*
 *
 */

/*
TESTS
[[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]]
[[1,1,1],[1,0,1],[1,1,1]]
[[1,1,1,0,0,0,0,0,0],[1,0,1,0,1,1,1,1,1],[1,1,1,0,0,0,0,0,0]]
[[0,1,0,1,1,1,1,1,1,0],[0,0,0,1,0,0,0,0,0,0],[0,0,1,1,1,0,0,0,1,0],[0,0,0,1,1,0,0,1,1,0],[0,1,0,0,1,0,1,1,0,1],[0,0,0,1,0,1,0,1,1,1],[0,1,0,0,1,0,0,1,1,0],[0,1,0,1,0,0,0,1,1,0],[0,1,1,0,0,1,1,0,0,1],[1,0,1,1,0,1,0,1,0,1]]
*/
