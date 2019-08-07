class Solution {
   vector<vector<int>> reachable;
   int n, m;
   vector<vector<int>> g;
   int dx[4] = {0, 1, 0, -1};
   int dy[4] = {1, 0, -1, 0};

   bool valid(int x, int y) {
      if (x < 0) return false;
      if (x >= n) return false;
      if (y < 0) return false;
      if (y >= m) return false;
      return true;
   }

   void bfs(deque<pair<int, int>> &start) {
      vector<vector<bool>> visited(n, vector<bool>(m, false));
      for (const auto & pr : start) {
         visited[pr.first][pr.second] = true;
         reachable[pr.first][pr.second] ++;
      }

      while(!start.empty()) {
         auto top = start.front();
         start.pop_front();
         int x = top.first; int y = top.second;
         for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i]; int ny = y + dy[i];
            if (!valid(nx, ny)) continue;
            if (visited[nx][ny]) continue;
            if (g[nx][ny] >= g[x][y]) {
               visited[nx][ny] = true;
               reachable[nx][ny]++;
               start.emplace_back(nx, ny);
            }
         }
      }
   }
public:
   vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
      if (matrix.empty()) return {};
      n = matrix.size();
      m = matrix[0].size();
      reachable.resize(n, vector<int>(m, 0));
      g = move(matrix);

      // pacific
      deque<pair<int, int>> boundary;
      for (int i = 0; i < m; ++i) {
         boundary.emplace_back(0, i);
      }
      for (int i = 1; i < n; ++i) {
         boundary.emplace_back(i, 0);
      }
      bfs(boundary);

      // altalenta
      for (int i = 0; i < n; ++i) {
         boundary.emplace_back(i, m - 1);
      }

      for (int i = 0; i < m - 1; ++i) {
         boundary.emplace_back(n - 1, i);
      }
      bfs(boundary);

      vector<pair<int, int>> ret;
      for (int x = 0; x < reachable.size(); ++x) {
         for (int y = 0; y < reachable[x].size(); ++y) {
            if (reachable[x][y] == 2) {
               ret.emplace_back(x, y);
            }
         }
      }

      return ret;
   }
};
