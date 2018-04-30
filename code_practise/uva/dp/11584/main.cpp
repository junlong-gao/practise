#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

namespace Solution{
    using namespace std;
    const int maxn = 1000 + 5;
    string s;
    int n;
    bool p[maxn][maxn];
    int dp[maxn];

    void readInput(){
        memset(p, false, sizeof(p));
        cin >> s; n = s.length();
        for(int i = 0; i < n; ++i){
            int j, k; j = i - 1; k = i + 1;
            while(j>=0 && k <n && s[j] == s[k]){
                p[j+1][k+1] = true;
                j--; k ++;
            }
        }
        for(int i = 0; i < n - 1; ++i){
            int j,k; j=i; k = i + 1;
            while(j >= 0 && k < n && s[j] == s[k]){
                p[j+1][k+1] = true;
                j--; k++;
            }
        }
    }

    
    void run(){
        int T; cin >> T;
        while(T--){
            readInput();
            memset(dp, 0, sizeof(dp));
            dp[0] = 0; dp[1] = 1;
            for(int i = 2; i <= n; ++i){
                dp[i] = dp[i - 1] + 1;
                for(int j = i - 1; j >= 1; --j){
                    if(p[j][i]){
                        dp[i] = min(dp[i], dp[j-1] + 1);
                    }
                }
            }
            cout << dp[n] << endl;
        }
    }
}

int main(){
    Solution::run();
    return 0;
}
