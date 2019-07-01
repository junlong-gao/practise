class Solution {
    unordered_map<int, unordered_map<int, int>> dp;
    int solve(int n, int k) {
        if (k == 1) return n;
        if (n == 0) return 0;
        if (dp.count(n) && dp[n].count(k)) return dp[n][k];
        
        int &ans = dp[n][k];
 
        int l = 1, r = n + 1;
        while (l + 1 != r) {
            int mid = (l + r) / 2;
            if (solve(mid - 1, k - 1) <= solve(n - mid, k)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        
        ans = 1 + max(solve(l - 1, k - 1), solve(n - l, k));
        return ans;
    }
public:
    int superEggDrop(int K, int N) {
        return solve(N, K);
    }
};
