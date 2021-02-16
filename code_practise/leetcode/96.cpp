class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1);
        for (int i = 0; i <= n; ++i) {
            if (i == 0) {
                dp[i] = 1;
            } else {
                dp[i] = 0;
                for (int l = 0; l < i; ++l) {
                    dp[i] += dp[l] * dp[i - 1 - l];
                }
            }
        }
        return dp[n];
    }
};