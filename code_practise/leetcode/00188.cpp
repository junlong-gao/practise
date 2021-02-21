class Solution {
/*
dp[n][k] = the max profit you can obtain for first n days with k transactions
at most
case 1: sell at day n, bought at day 0 < j < n
dp[j][k-1] + price[n - 1] - price[j - 1] = dp[j][k-1] - price[j - 1] + price[n - 1]
case 2: not sell
dp[n-1][k]

dp[0][k] = 0 for all k >= 0
dp[n][0] = 0 for all n >= 0

time complexity = O(number of entries/subproblems) * O(ave cost of solving each problem) = O(n^2k)

after optimization:
time complexity = O(n * k)
space = O(n)
*/
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<int>> dp(2, vector<int>(prices.size() + 1, 0));
        int n = prices.size();
        for (int kk = 0; kk <= k; kk++) {
            int runningMax = INT_MIN;
            for (int i = 0; i<= n; ++i) {
                int &ans = dp[kk % 2][i];
                
                if (kk == 0) {
                    ans = 0;
                } else if (i == 0) {
                    ans = 0;
                } else {
                    ans = dp[kk%2][i-1];
                    if (i > 1) {
                        ans = max(ans, runningMax + prices[i - 1]);
                    }
                    runningMax = max(runningMax, dp[(kk-1+2)%2][i - 1] - prices[i - 1]);
                }
            }
        }
        return dp[k%2][n];
    }
};
