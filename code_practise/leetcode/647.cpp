class Solution {
public:
    int countSubstrings(string S) {
        vector<vector<bool>> dp(S.size(), vector<bool>(S.size(), false));
        int ret = 0;
        for (int l = 1; l <= S.size(); ++l) {
            for (int i = 0; i + l - 1 < S.size(); ++i) {
                int j = i + l - 1;
                if (i == j) {
                    dp[i][j] = true;
                } else if (i == j - 1) {
                    dp[i][j] = S[i] == S[j];
                } else {
                    dp[i][j] = (S[i] == S[j]) && dp[i+1][j-1];
                }
                if (dp[i][j]) {
                    ret++;
                }
            }
        }
        
        return ret;
    }
};
