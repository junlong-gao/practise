class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        vector<vector<int>> dp(A.size(), vector<int>(B.size(), 0));
        int ret = 0;
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < B.size(); ++j) {
                if (i == 0 || j == 0) {
                   if (A[i] == B[j]) {
                       dp[i][j] = 1;
                   }
                } else {
                    if (A[i] == B[j]) {
                        dp[i][j] = dp[i-1][j-1] + 1;
                    }
                }
                ret = max(ret, dp[i][j]);
            }
        }
        
        return ret;
    }
};