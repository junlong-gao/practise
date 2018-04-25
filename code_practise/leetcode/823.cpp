class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& A) {
        sort(A.begin(), A.end());
        const int mod = 1e9 + 7;
        auto add = [&](int l, int r) {
            return (l + r) % mod;
        };
        auto mul = [&](int l, int r) {
            long long ll = l;
            long long rr = r;
            return (ll * rr) % mod;
        };
        
        int n = A.size();
        vector<int> dp (n);
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (A[i] % A[j] != 0) continue;
                for (int k = 0; k < i; ++k) {
                    if (A[i] != A[j] * A[k]) continue;
                    dp[i] = add(dp[i], mul(dp[j], dp[k]));
                }
            }
        }
        int ret = 0;
        for (auto v : dp) {
            ret = add(ret, v);
        }
        return ret;
    }
};
