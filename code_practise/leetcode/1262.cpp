class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        // dp[i][d] = max sum of numbers from 0...i such that its
        // residue is d;
        // dp[0][d] = -1 if nums[0] % 3 != d, else nums[0]
        // dp[i][d] = max(dp[i-1][d], dp[i-1][d'] + nums[i]), check -1 first;
        vector<vector<int>> dp(nums.size(), vector<int>(3, -1));

        for (int i = 0; i < nums.size(); ++i) {
            for (int d = 0; d < 3; ++d) {
                if (i == 0) {
                    if (nums[0] % 3 == d) {
                        dp[i][d] = nums[0];
                    } else {
                        if (d == 0) {
                            dp[i][d] = 0;
                        } else {
                            dp[i][d] = -1;
                        }
                    }
                } else {
                    dp[i][d] = dp[i-1][d];

                    int dprime = (3 + d - nums[i] % 3) % 3;
                    if (dp[i-1][dprime] != -1) { // since we +nums[i]
                        dp[i][d] = max(dp[i][d], dp[i-1][dprime] + nums[i]);
                    }
                }
            }
        }

        return dp[nums.size() - 1][0];
    }
};