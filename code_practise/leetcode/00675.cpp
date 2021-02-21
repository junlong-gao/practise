class Solution {
  int dx[4] = {0, 1, 0, -1};
  int dy[4] = {1, 0, -1, 0};
  vector<vector<int>> g;
  vector<vector<bool>> visited;
  int n, m;
  
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
    if (g[x][y] == 0) {
      return false;
    }
    return true;
  }
  
  int minDist(pair<int, int> src, pair<int, int> dst) {
    if (src == dst) {
      return 0;
    }
    
    visited = vector<vector<bool>>(n, vector<bool>(m, false));
    vector<vector<int>> dist(n, vector<int>(m, -1));
    
    deque<pair<int, int>> q{src};
    dist[src.first][src.second] = 0;
    visited[src.first][src.second] = true;
    
    while(!q.empty()) {
      auto top = q.front();
      q.pop_front();
      int soFar = dist[top.first][top.second];
      for (int i = 0; i < 4; ++i) {
        int nx = top.first + dx[i];
        int ny = top.second + dy[i];
        if (canMove(nx, ny)) {
        /*
        be careful, this opt will bite you in an interview when src == dst, see line 25
        */
          if (nx == dst.first && ny == dst.second) {
            return soFar + 1;
          }
          
          dist[nx][ny] = soFar + 1;
          visited[nx][ny] = true;
          q.emplace_back(nx, ny);
        }
      }
    }
    
    return -1;
  }
public:
    int cutOffTree(vector<vector<int>>& forest) {
      g = move(forest);
      map<int, pair<int, int>> trees;
      if (g.empty()) {
        return 0;
      }
      n = g.size();
      m = g[0].size();
      
      for (int i = 0; i < n; ++i) {
        for (int j= 0; j < m; ++j) {
          if (g[i][j] > 1) {
            trees[g[i][j]] = make_pair(i, j);
          }
        }
      }
      pair<int, int> cur = {0, 0};
      int totalCount = 0;
      for (auto & it : trees) {
        auto dst = it.second;
        
        int next = minDist(cur, dst);
        if (next < 0) {
          return -1;
        }
        
        totalCount += next;
        //cout << it.first << " " << next << endl;
        cur = dst;
      }
      
      return totalCount;
    }
};
