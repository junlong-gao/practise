class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int n = nums.size();
        int total = 0;
        for (int i = 0; i < nums.size(); ++i) {
            total += nums[i];
        }
        vector<vector<int>> dp(n + 1, vector<int>(2 * total + 1, 0));
        for (int count = 0; count <= n; ++count) {
            if (count == 0) { dp[0][total] = 1; continue; }
            for (int s = -total; s <= total; ++s) {
                int idx = s + total;
                dp[count][idx] = 0;
                if (s - nums[count - 1] >= -total) dp[count][idx] += dp[count - 1][idx - nums[count - 1]];
                if (s + nums[count - 1] <= total)  dp[count][idx] += dp[count - 1][idx + nums[count - 1]]; 
            }
        }
        return dp[n][S + total];
    }
};
