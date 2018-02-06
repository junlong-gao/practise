#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
using namespace std;

class Solution {
  int t;
  int dx[4] = {0, 1, 0, -1};
  int dy[4] = {1, 0, -1, 0};
  
  vector<vector<int>> g;
  vector<vector<bool>> visited;
  int n;
  
  bool canMove(int x, int y) {
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
  
  bool check() {
    if (!canMove(0, 0)) {
      return false;
    }
    //cout << "bfs" <<endl;
    deque<pair<int, int>> q;
    q.push_back({0, 0});
    visited[0][0] = true;
    while (!q.empty()) {
      auto top = q.front();
      q.pop_front();
      int x = top.first, y = top.second;
      //cout << "@@" <<x << " " << y << endl;
      for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if (!canMove(nx, ny)) {
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
    //cout << lo << ", " << hi << endl;
    if (hi == lo) {
      return lo;
    }
    
    for (int i = 0; i < n; ++i) {
      visited[i].resize(n);
      fill(visited[i].begin(), visited[i].end(), false);
    }
    
    t = lo + (hi - lo)/2;
    if (check()) {
      return search(lo, t);
    } else {
      return search(t + 1, hi);
    }
  } 
public:
  int swimInWater(vector<vector<int>> grid) {
    if (grid.empty()) return 0;
    n = grid.size();
    visited.resize(n);
    swap(g, grid);
    return search(0, n*n);
  }
};

int main() {
  Solution s;
  assert(3 == s.swimInWater({{0,1},{2,3}}));
  assert(3 == s.swimInWater({{3,1},{2,1}}));
  assert(16 ==
  s.swimInWater({{0,1,2,3,4},{24,23,22,21,5},{12,13,14,15,16},{11,17,18,19,20},{10,9,8,7,6}}));
}

/*
binary search in t...
This really should be medium difficulty
*/
