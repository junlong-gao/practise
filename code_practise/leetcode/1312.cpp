class Solution {
public:
    int minInsertions(string s) {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), INT_MAX));
        for (int l = 1; l <= s.size(); ++l) {
            for (int i = 0; i + l - 1 < s.size(); ++i) {
                int j = i + l - 1;
                if (l == 1) {
                    dp[i][j] = 0;
                } else {
                    if (s[i] == s[j]) {
                        dp[i][j] = l == 2 ? 0 : dp[i + 1][j - 1];
                    } else {
                        dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
                    }
                }
            }
        }
        return dp[0][s.size() - 1];
    }
};