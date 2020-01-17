class Solution {
public:
    int countPalindromicSubsequences(string S) {
        const long long m = 1e9 + 7;
        vector<vector<vector<long long>>>
            dp(S.size(), vector<vector<long long>>(S.size(), vector<long long>(4, 0)));

        long long ret = 0;
        for (int l = 1; l <= S.size(); ++l) {
            for (int i = 0; i + l - 1 < S.size(); ++i) {
                for (int k = 0; k < 4; ++k) {
                    int j = i + l - 1;
                    if (l == 1) {
                        dp[i][j][k] = S[i] - 'a' == k;
                    } else if (l == 2) {
                        if (S[i] - 'a' == k && S[j] - 'a' == k) {
                            dp[i][j][k] = 2;
                        } else if (S[i] - 'a' == k || S[j] - 'a' == k) {
                            dp[i][j][k] = 1;
                        }
                    } else {
                        if (S[i] - 'a' == k && S[j] - 'a' == k) {
                            dp[i][j][k] = 2;
                            for (int p = 0; p < 4; ++p) {
                                dp[i][j][k] = (dp[i][j][k] + dp[i + 1][j - 1][p]) % m;
                            }
                        } else if (S[i] - 'a' == k) {
                            dp[i][j][k] = dp[i][j - 1][k];
                        } else if (S[j] - 'a' == k) {
                            dp[i][j][k] = dp[i + 1][j][k];
                        } else {
                            dp[i][j][k] = dp[i + 1][j - 1][k];
                        }
                    }
                    if (l == S.size()) {
                        ret = (ret + dp[i][j][k]) % m;
                    }
                }
            }
        }
        return ret;
    }
};
