
class Solution {
  vector<int> count_1, count_0;
  int countZero(const string& s) {
    int ret = 0;
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] == '0') ret++;
    }
    return ret;
  }

 public:
  int findMaxForm(vector<string>& strs, int m, int n) {
    for (const auto& s : strs) {
      count_0.push_back(countZero(s));
      count_1.push_back(s.length() - count_0.back());
    }
    vector<vector<int>> dp(m + 1, vector<int>(n+1, 0));
    for (int i = 0; i < strs.size(); ++i) {
        for (int zeros = m; zeros >= 0; --zeros) {
            for (int ones = n; ones >= 0; --ones) {
                if (count_0[i] > zeros || count_1[i] > ones) continue;
                dp[zeros][ones] = max(dp[zeros][ones], dp[zeros - count_0[i]][ones - count_1[i]] + 1);
            }
        }
    }
    return dp[m][n];
  }
};

