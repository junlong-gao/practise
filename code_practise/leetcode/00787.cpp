class Solution {
  unordered_map<int, unordered_map<int, int>> dp;
  unordered_map<int, unordered_map<int, int>> w;
  int s;
  int dfs(int d, int k) {
    if (d == s) {
      return 0;
    }
    
    if (k == 0) {
      if (w.count(d) && w[d].count(s)) {
        return w[d][s];
      }
      return INT_MAX;
    }

    if (dp.count(d) && dp[d].count(k)) {
      return dp[d][k];
    }
    int& ret = dp[d][k];
    ret = INT_MAX;
    for (auto pr : w[d]) {
      int u = pr.first;
      int p = dfs(u, k - 1);
      if (p == INT_MAX) continue;
      ret = min(ret, p + w[d][u]);
    }
    return ret;              
  }
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
      if (src == dst) return 0;
      for (int i = 0; i < flights.size(); ++i) {
        w[flights[i][1]][flights[i][0]] = flights[i][2];
      }
      s = src;
      int ret = dfs(dst, K);
      return ret == INT_MAX ? -1 : ret;
    }
};
