class Solution {
   vector<vector<int>> dp;
   int search(int i , int j, const string &s) {
      if (dp[i][j] != INT_MAX) return dp[i][j];
      int &ret = dp[i][j];
      if (i == j) return ret = 1;
      if (s[i] != s[j]) {
         /* there is a way to separate opt into 2 parts */
         for (int k = i; k < j; ++k) {
            ret = min(ret, search(i, k, s) + search(k + 1, j, s));
         }
      } else {
         /* all opt must not be separated */
         ret = search(i, j - 1, s);
      }

      return ret;
   }
public:
   int strangePrinter(string s) {
      if (s.empty()) return 0;
      dp.resize(s.size(), vector<int>(s.size(), INT_MAX));
      return search(0, s.size() - 1, s);
   }
};
