#pragma GCC optimise ("Ofast")
int f = [](){ios::sync_with_stdio(false); cin.tie(0); return 0;}();

class Solution {
public:
    /*
    Consider an alternative way of solving this using dp[i][j] = # palindrom in
    S[i,j] Let S[i] = S[j] = a, we can divide palindroms into 2 types S[i]_S[j]
    and the rest. But now we have the problem: S[i]_S[j] will be one to one
    mapped to dp[i + 1][j - 1], plus a and aa. but the rest is not so easy:
    rest is dp[i + 1][j - 1] eliminates the palindroms not ending in a.

    Now that we know the set a(dp[i+1][j-1])a and dp[i+1][j-1] collide,
    what is the collision?
    ===
    str: a__a__a__a
    idx: i  s  e  j
       S be the collection a(dp[i+1][j-1])a and T be dp[i+1][j-1]
       when will they collide? let str be such a collision, then
       str is dp[i+1][j-1] and of the form a__a, so it is in dp[s][e],
       but not all of dp[s][e] as it contains palindrom not ending in a. 
       str is also in dp[s + 1][e - 1].
       let str be in d[s + 1][e - 1], then a(str)a is both in a(dp[i+1][j-1])a
       and dp[i+1][j-1]
       so the collision set is dp[s+1][e-1]

       --> dp[i+1][j-1] + dp[i+1][j-1] - dp[s+1][e-1]
    std: a__a__a
       for a of len = 1 -> counted in dp[i+1][j-1]
       
       S be the collection a(dp[i+1][j-1])a and T be dp[i+1][j-1]
       when will they collide? Impossible, as dp[i+1][j-1] cannot contain
       palindroms of the form a_a.
       --> 1 + 2 * dp[i+1][j-1]

    std: a__a
       for a of len = 1 and 2: not counted in dp[i+1][j-1]

       No collision possible.
       --> 2 + 2 * dp[i+1][j-1]

    picking palindroms not ending in a requires introducing a new state. 
    */
    int countPalindromicSubsequences(string S) {
        const long long m = 1e9 + 7;
        vector<int> n(S.size(), -1), p(S.size(), -1);
        vector<vector<long long>> dp(S.size(), vector<long long>(S.size(), 0));

        {
            vector<int> t(4, -1);
            for (int i = 0; i < S.size(); ++i) {
                if (t[S[i] - 'a'] != -1) {
                    p[i] = t[S[i] - 'a'];
                }
                t[S[i] - 'a'] = i;
            }
        }
        {
            vector<int> t(4, -1);
            for (int i = S.size() - 1; i >= 0; --i) {
                if (t[S[i] - 'a'] != -1) {
                    n[i] = t[S[i] - 'a'];
                }
                t[S[i] - 'a'] = i;
            }
        }

        for (int l = 1; l <= S.size(); ++l) {
            for (int i = 0; i + l - 1 < S.size(); ++i) {
                int j = i + l - 1;
                if (l == 1) {
                    dp[i][j] = 1;
                } else if (l == 2) {
                    dp[i][j] = 2;
                } else {
                    if (S[i] == S[j]) {
                        if (n[i] != -1 && p[j] != -1 && n[i] < p[j] && n[i] < j && p[j] > i) {
                            dp[i][j] = ((2*dp[i+1][j-1])%m + (m-dp[n[i] + 1][p[j]-1])%m)%m;
                        } else if (n[i] != -1 && p[j] != -1 && n[i] == p[j] && n[i] < j && p[j] > i) {
                            dp[i][j] = (1 + (2 * dp[i+1][j-1] % m))%m;
                        } else {
                            dp[i][j] = (2 + (2 * dp[i+1][j-1] % m))%m;
                        }
                    } else {
                        dp[i][j] = ((dp[i][j-1] + dp[i+1][j])%m + (m - dp[i+1][j-1])%m)%m;
                    }
                }
            }
        }
        return dp[0][S.size() - 1];
    }
};
