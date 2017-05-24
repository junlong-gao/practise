#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
using l_int = long long;

const l_int M = 1000000007L;
const l_int maxn = 205;
//dp[i][j] = number of common subsequece in [0...i) 
//and [l...l+j+1)  AND ALL SHARE THE SAME START s[l]
//it is common trick in dp that same start can be realized 
//as BOUNDARY CONDITION and the FAMILIAR LCS thinking can be applied

int main() {
    int T; cin >> T;
    l_int dp[maxn][maxn];
    l_int n, rst;
    string s;
    while(T--){
        rst = 0;
        cin >> s; n = s.length();
        for(int l = 1; l < n; ++l){
            memset(dp, 0, sizeof(dp));
            int n1 = l; int n2 = n - l - 1;
            for(int i = 1; i <= n1; ++i){
                dp[i][0] = dp[i-1][0] + (s[i-1] == s[l]? 1 : 0);
            }
            for(int i = 1; i <= n1; ++i){
                for(int j = 1; j <= n2; ++j){
                    dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % M;
                    if(s[i-1]!=s[l+j])
                        dp[i][j] = (dp[i][j] - dp[i-1][j-1] + M) % M;
                    //if they share the different ending, we know that 
                    //all common subsequence must be in the [0..i-1) and [l..j+l-1)
                    //and it is added twice
                    //if they share the same ending, it SHOULD BE ADDED TWICE
                    //since one of the copy will AUTOMATICALLY subfixed by s[i-1]
                    //and s[l+j] to form a set of new common subsequences end in s[i-1]
                    //s[l+j]
                }
            }
            rst = (rst + dp[n1][n2])%M;
        }
        cout << rst << endl;
    }
    return 0;
}

