class Solution {
public:
    int maxVacationDays(vector<vector<int>>& flights, vector<vector<int>>& days) {
        int n = flights.size();
        if (n == 0) return 0;
        int k = days[0].size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        // city 0 is reachable at week -1
        dp[0][1] = 0;
        int best = 0;
        for (int j = 0; j < k; ++j) {
            for (int i = 0; i < n; ++i) {
                if (i == 0 && j == 0) { dp[0][0] = days[0][0]; continue;}
                dp[i][j%2] = -1;
                for (int l = 0; l < n; ++l) {
                    if ((l == i || flights[l][i] == 1) && dp[l][(j + 1) % 2] >= 0) {          
                        dp[i][j%2] = std::max(dp[i][j%2], dp[l][(j + 1) % 2] + days[i][j]);
                    }
                }
                if (j == k - 1) {
                    best = std::max(best, dp[i][j%2]);
                }
            }
        }
        return best;
    }
};
