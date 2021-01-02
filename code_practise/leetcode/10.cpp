class Solution {
public:
    bool isMatch(string s, string p) {
       vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));

       for (int i = 0; i <= s.length(); ++i) {
          for (int j = 0; j <= p.length(); ++j) {
             if (i == 0 && j == 0) {
                dp[i][j] = true;
             } else if (j == 0 && i > 0) {
                dp[i][j] = false;
             } else if (i == 0 && j > 0) {
                if (p[j-1] == '*') {
                   dp[i][j] = dp[i][j-2];
                } else {
                   dp[i][j] = false;
                }
             } else {
                if (p[j-1] == '*') {
                   dp[i][j] = dp[i][j-2] || (dp[i-1][j] && (p[j-2]=='.' || s[i-1] == p[j-2]));
                } else if (p[j-1]=='.'){
                   dp[i][j]=dp[i-1][j-1];
                } else {
                   dp[i][j]=dp[i-1][j-1]&&(s[i-1]==p[j-1]);
                }
             }
          }
       }
       return dp[s.size()][p.size()];
    }
};
