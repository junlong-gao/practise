class Solution {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(s.length(), vector<int>(s.length(), 0));
        for (int l = 1; l <= s.length(); ++l) {
            for (int i = 0; i + l - 1 < s.length(); ++i) {
                int j = i + l - 1;
                if (l == 1) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = max(dp[i][j], (s[i] == s[j] ? 2 : 0) + dp[i + 1][j - 1]);
                    dp[i][j] = max(dp[i][j], dp[i + 1][j]);
                    dp[i][j] = max(dp[i][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[0][s.length() - 1];
    }
};
