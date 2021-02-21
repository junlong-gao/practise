/*
dp[i][j] = longest fib-like seq end in A[i][j]
         = max_{0 <= k < i} {dp[k][i] + 1 if A[k] + A[i] = A[j]}
*/

class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        unordered_map<int, int> t;
        int n = A.size();
        vector<vector<int>> dp(n, vector<int>(n, 2));
        for (int i = 0; i < A.size(); ++i) {
            t[A[i]] = i;
        }
        int best = 0;
        for (int j = 2; j < n; ++j) {
            for (int i = 1; i < j; ++i) {
                int d = A[j] - A[i];
                if (t.count(d) == 0 || t[d] >= i) {
                    //dp[i][j] = 0; !!
                    continue;
                }
                dp[i][j] = dp[t[d]][i] + 1;
                best = max(best, dp[i][j]);
            }
        }
        return best;
    }
};