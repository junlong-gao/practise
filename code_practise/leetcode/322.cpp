class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<vector<int>> dp(coins.size(), vector<int>(amount + 1, -1));
        for (int i = 0; i < coins.size(); ++i) {
            for (int v = 0; v <= amount; ++v) {
                if (i == 0) {
                    if (v % coins[i] == 0) {
                        dp[i][v] = v / coins[i];
                    } else {
                        dp[i][v] = -1;
                    }
                } else if (v == 0) {
                    dp[i][v] = 0;
                } else {
                    dp[i][v] = dp[i-1][v];
                    if (v >= coins[i] && dp[i][v-coins[i]] != -1) {
                        if (dp[i][v] == -1) {
                            dp[i][v] = dp[i][v-coins[i]] + 1;
                        } else {
                            dp[i][v] = min(dp[i][v], dp[i][v-coins[i]] + 1);
                        }
                    }
                }
            }
        }
        return dp[coins.size() - 1][amount];
    }
};