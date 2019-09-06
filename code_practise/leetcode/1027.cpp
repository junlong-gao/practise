class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        vector<unordered_map<int, int>> mp(A.size());
        for (int i = 0; i < A.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                mp[i][A[j] - A[i]] = j;
            }
        }
        
        vector<vector<int>> dp(A.size(), vector<int>(A.size(), 2));
        int m = 2;
        for (int i = 2; i < A.size(); ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (mp[j].count(A[j] - A[i])) {
                    dp[i][j] = dp[j][mp[j][A[j] - A[i]]] + 1;
                    m = max(dp[i][j], m);
                }
            }
        }
        
        return m;
    }
};
