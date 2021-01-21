class Solution {
public:
    int countSubstrings(string s) {
        int ret = 0;
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        
        for (int l = 1; l <= s.size(); ++l) {
            for (int i = 0; i + l - 1 < s.size(); ++i) {
                int j = i + l - 1;
                if (l == 1) {
                    dp[i][j] = true;
                } else if (l == 2) {
                    dp[i][j] = (s[i] == s[j]);
                } else {
                    dp[i][j] = dp[i+1][j-1] && (s[i] == s[j]);
                }
                
                if (dp[i][j]) {
                    ret++;
                }
            }
        }
        
        return ret;
        
    }
};
