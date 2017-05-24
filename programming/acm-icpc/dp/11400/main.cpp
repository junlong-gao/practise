#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

namespace Solution{
    using namespace std;
    const int maxn = 1000 + 5;
    const int INF = 1000000000;
    struct lamp{
        int v, k, c, l;
        bool operator<(const lamp& other) const{
            return v < other.v;
        }

    } lamp[maxn];
    int n, dp[maxn], s[maxn];

    void readInput(){
        for(int i = 1; i <= n; ++i){
            cin >>lamp[i].v >>lamp[i].k>>lamp[i].c>>lamp[i].l;
        }
        sort(lamp + 1, lamp + n + 1);
        s[0] =0;
        for(int i = 1; i <= n; ++i){
            s[i] = s[i-1] + lamp[i].l;
        }
        memset(dp, 0, n + 1);

    }

    
    void run(){
        while(cin >> n && n){
            readInput();
            dp[1] = lamp[1].k + lamp[1].c * lamp[1].l;
            cerr << dp[1] << endl;
            for(int i = 2; i <=n; ++i){
                dp[i] = INF;
                for(int j = i - 1; j >=0; --j){
                    dp[i] = min(dp[i], dp[j] + lamp[i].c*(s[i]-s[j]) + lamp[i].k);
                    cerr << i << " " << dp[i] << endl;
                }
            }
            cout  << dp[n] << "\n";
        }

    }
}

int main(){
    Solution::run();
    return 0;
}
