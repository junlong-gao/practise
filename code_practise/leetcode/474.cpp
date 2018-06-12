
class Solution {
  vector<int> count_1, count_0;
  int countZero(const string& s) {
    int ret = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '0') ret++;
    }
    return ret;
  }
  unordered_map<int, unordered_map<int, unordered_map<int, int>>> dp;
  bool computed(int idx, int m, int n) {
    if (dp.count(idx) == 0) return false;
    if (dp[idx].count(m) == 0) return false;
    if (dp[idx][m].count(n) == 0) return false;
    return true;
  }
  int solve(int idx, int m, int n) {
    if (computed(idx, m, n)) return dp[idx][m][n];
    if (idx == 0) {
        if (count_0[idx] > m || count_1[idx] > n) return dp[idx][m][n] = 0;
        return 1;
    }

    dp[idx][m][n] = solve(idx - 1, m, n);
    if (count_0[idx] <= m && count_1[idx] <= n) {
        dp[idx][m][n] = max(dp[idx][m][n], solve(idx - 1, m - count_0[idx], n - count_1[idx]) + 1);
    }
                        
    return dp[idx][m][n];
  }

 public:
  int findMaxForm(vector<string>& strs, int m, int n) {
    for (const auto& s : strs) {
      count_0.push_back(countZero(s));
      count_1.push_back(s.length() - count_0.back());
    }
    return solve(strs.size() - 1, m, n);
  }
};

