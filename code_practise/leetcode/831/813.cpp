class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        vector<vector<double>> dp(A.size() + 1, vector<double>(K + 1, 0));
        vector<double> p{0};
        for (int i = 0; i < A.size(); ++i) {
            p.push_back(p.back() + A[i]);
        }
        for (int i = 1; i <= A.size(); ++i) {
            for (int k = 1; k <= K; ++k) {
                if (i == 1) {
                    dp[i][k] = A[0];
                } else if (k == 1) {
                    dp[i][k] = p[i] / i;
                } else {
                    for (int j = i - 1; j >= 1; --j) {
                        dp[i][k] = max(dp[i][k], dp[j][k - 1] + (p[i] - p[j]) / (i - j));
                    }
                }
            }
        }
        return dp[A.size()][K];
    }
};
