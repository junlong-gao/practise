class Solution {
  int dx[4] = {0, 1, 0, -1};
  int dy[4] = {1, 0, -1, 0};
  
  vector<vector<int>> g;
  vector<vector<bool>> visited;
  int n;
  
  bool canMove(int x, int y, int t) {
    if (x >= n || x < 0 || y >= n || y < 0) {
      return false;
    }
    if (visited[x][y]) {
      return false;
    }
    if (g[x][y] > t) {
      return false;
    }
    return true;
  }
  
  bool check(int t) {
    for (int i = 0; i < n; ++i) {
      visited[i].resize(n);
      fill(visited[i].begin(), visited[i].end(), false);
    }

    deque<pair<int, int>> q;
    q.push_back({0, 0});
    visited[0][0] = true;
    while (!q.empty()) {
      auto top = q.front();
      q.pop_front();
      int x = top.first, y = top.second;
      for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (!canMove(nx, ny, t)) {
          continue;
        }
        visited[nx][ny] = true;
        if (nx == (n - 1) && ny == (n - 1)) {
          return true;
        }
        q.push_back({nx, ny});
      }
    }
    return false;
  }
  
  int search(int lo, int hi) {
    while (hi - lo > 1) {
        int t = lo + (hi - lo)/2;
        if (check(t)) {
           hi = t;
        } else {
           lo = t;
        }
    }
      
    return hi;
  } 
public:
  int swimInWater(vector<vector<int>> grid) {
    if (grid.empty()) return 0;
    n = grid.size();
    visited.resize(n);
    swap(g, grid);

    return search(g[0][0] - 1, n*n - 1);
  }
};
