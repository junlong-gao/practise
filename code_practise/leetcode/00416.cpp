class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (auto e : nums) {
            sum += e;
        }
        if (sum % 2) {
            return false;
        }
        
        sum /= 2;
        vector<vector<bool>> dp(nums.size(), vector<bool>(sum + 1, false));
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j <= sum; ++j) {
                if (i == 0) {
                    dp[i][j] = (j == nums[i])? true : false;
                } else if (j == 0) {
                    dp[i][j] = true;
                } else {
                    dp[i][j] = dp[i-1][j];
                    if (j >= nums[i]) {
                        dp[i][j] = dp[i][j] || dp[i-1][j-nums[i]];
                    }
                }
            }
        }
        return dp[nums.size() - 1][sum];
    }
};