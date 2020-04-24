class Solution {
    /*
    dp[n][r] =
       | n = 0 and r = 0 ->
          0
       | n = 0 ->
          -1
       | _ ->
          let t = (k + r - num[n-1]) in
          if (dp[n-1][t] == -1) dp[n-1][r]
          else max(dp[n-1][r], dp[n-1][t] + num[n-1])

        XXX use -1 for impossible cases so max above works.
    */
    int rem(int val, int k, int T) {
        k += (val / T + 1) * T;
        assert (k >= val);
        return (k - val) % T;
    }
public:
    int maxSumDivThree(vector<int>& nums) {
        int T = 3;
        vector<vector<int>> dp(nums.size() + 1, vector<int>(T, -1));
        for (int i = 0; i <= nums.size(); ++i) {
            for (int k = 0; k < T; ++k) {
                if (i == 0) {
                    if (k == 0) {
                        dp[i][k] = 0;
                    }
                } else {
                    dp[i][k] = dp[i - 1][k];
                    int r = dp[i - 1][rem(nums[i - 1], k, T)];
                    if (r >= 0) {
                        dp[i][k] = max(dp[i][k], r + nums[i - 1]);
                    }
                }
            }
        }