/*
 * [407] Trapping Rain Water II
 *
 * https://leetcode.com/problems/trapping-rain-water-ii/description/
 *
 * algorithms
 * Hard (37.96%)
 * Total Accepted:    15.7K
 * Total Submissions: 41.3K
 * Testcase Example:  '[[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]'
 *
 * Given an m x n matrix of positive integers representing the height of each
 * unit cell in a 2D elevation map, compute the volume of water it is able to
 * trap after raining.
 *
 *
 * Note:
 * Both m and n are less than 110. The height of each unit cell is greater than
 * 0 and is less than 20,000.
 *
 *
 * Example:
 *
 * Given the following 3x6 height map:
 * [
 * ⁠ [1,4,3,1,3,2],
 * ⁠ [3,2,1,3,2,4],
 * ⁠ [2,3,3,2,3,1]
 * ]
 *
 * Return 4.
 *
 *
 *
 *
 *
 * The above image represents the elevation map
 * [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]] before the rain.
 *
 *
 *
 *
 * After the rain, water is trapped between the blocks. The total volume of
 * water trapped is 4.
 *
 */
/*
 * Digestion:
 * For every cell, the water level it can trap = the minimal level of a the
 * highest cell of each path it can go to the boundary.
 * We maintain a boundary, starting from the original boundary, and use BFS
 * to iteratively update new inner cell's trapped water. Every time we pick the
 * minimal height cell. And we propagate the highest cell information into the
 * maintained boundary.
 *
 * Think single source shortest path.
 */
class Solution {
   vector<vector<int>> g;
   vector<vector<bool>> visited;
   int n, m;
   int dx[4] = {0, -1, 0, 1};
   int dy[4] = {1, 0, -1, 0};

   bool canMove(int x, int y) {
      if (x < 0 || x >= n) {
         return false;
      }
      if (y < 0 || y >= m) {
         return false;
      }
      if (visited[x][y]) {
         return false;
      }

      return true;
   }

   struct p {
      int x, y, h;
   };

public:
    int trapRainWater(vector<vector<int>>& heightMap) {
       std::swap(heightMap, g);
       n = g.size();
       if (n == 0) return 0;
       m = g[0].size();
       visited = vector<vector<bool>>(n, vector<bool>(m, false));
       auto cp = [] (const p &l, const p &r) {
          return l.h > r.h; // cpp is minheap
       };

       std::priority_queue<p, std::vector<p>, decltype(cp)> q(cp);

       for (int i = 0; i < n; ++i) {
          q.push({i, 0,     g[i][0]});
          q.push({i, m - 1, g[i][m - 1]});
          visited[i][0] = true;
          visited[i][m - 1] = true;
       }

       for (int j = 1; j < m - 1; ++j) {
          q.push({0,     j, g[0][j]});
          q.push({n - 1, j, g[n - 1][j]});
          visited[0][j] = true;
          visited[n - 1][j] = true;
       }

       int ret = 0;
       while (!q.empty()) {
          auto top = q.top();
          q.pop();
          for (int i = 0; i < 4; ++i) {
             int x = top.x + dx[i];
             int y = top.y + dy[i];
             if (!canMove(x, y)) {
                continue;
             }

             visited[x][y] = true;
             //cout << x << ", " << y << ", " << top.h << ", " << g[x][y] << "," << ret << endl;
             ret += std::max(0, top.h - g[x][y]);
             q.push({x, y, std::max(top.h, g[x][y])});
          }
       }

       return ret;
    }
};

/*
 */

/*
TESTS
[[3,5,5],[5,4,5],[5,5,5]]
[[1, 1, 1],[1, 1, 1],[1, 1, 1]]
[[1, 2, 1],[2, 1, 3],[1, 2, 1]]
[[2, 2, 2],[2, 1, 2],[2, 2, 1]]
[[5,8,7,7],[5,2,1,5],[7,1,7,1],[8,9,6,9],[9,8,9,9]]
[[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
*/
