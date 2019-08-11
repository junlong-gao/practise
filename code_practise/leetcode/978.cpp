class Solution {
public:
    int maxTurbulenceSize(vector<int>& A) {
        vector<int> dp(A.size());
        vector<int> sign(A.size());
        
        for (int i = 1; i < A.size(); ++i) {
            sign[i] = A[i] - A[i - 1];
            if (sign[i] != 0) {
                sign[i] = sign[i] / abs(sign[i]);
            }
        }
        
        int maxW = 1;
        for (int i = 1; i < A.size(); ++i) {
            dp[i] = sign[i] * sign[i - 1] == -1? dp[i - 1] + 1
                    : (sign[i] == 0 ? 1 : 2);
            maxW = max(maxW, dp[i]);
        }
        
        return maxW;
    }
};
