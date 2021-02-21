class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int t = 0;
        for (int i = 0; i < nums.size(); ++i) {
            t += nums[i];
        }

        if (t % 2) return false;
        t /= 2;
        
        vector<vector<bool>> dp(nums.size(), vector<bool>(
            max(t, nums[0]) + 1, false));
        
        dp[0][nums[0]] = dp[0][0] = true;
        for (int i = 1; i < nums.size(); ++i) {
            dp[i][0] = true;
            for (int j = 0; j <= t; ++j) {
                dp[i][j] = dp[i - 1][j];
                if (j >= nums[i]) { dp[i][j] = dp[i][j] || dp [i - 1][j - nums[i]]; }
            }
        }
        
        return dp[nums.size() - 1][t];
    }
};

/*
another method is to brute force a solution by backtrack
the search tree can be considerably reduced as each number is
only in [0, 100], so by tracking the frequency of each number,
simply subtract the number from the state repeatedly to initiate a search.
*/