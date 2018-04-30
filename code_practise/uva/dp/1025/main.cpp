#include <iostream> 
#include <vector>
#include <cstring>
#include <algorithm>

namespace Solution{
    using namespace std;
    using vi = vector<int>;
    const int maxn = 50 + 5;
    const int maxt = 200 + 5;
    const int INF = 1000000000;
    int M1, M2, n, T;
    int kcase;
    int t[maxn];
    int dp[maxt][maxn];

    bool has_edge[maxt][maxn][2];

    bool readInput(){
        memset(has_edge, 0, sizeof(has_edge));
        cin >> n >> T;
        if(n == 0) return false;
        for(int i = 1; i <= n - 1; ++i){
            cin >> t[i];
        }
        cin >> M1;
        for(int i = 1; i <= M1; ++i){
            int d; cin >> d;
            for(int i = 1; d <= T &&i <= n-1; ++i){
                has_edge[d][i][0] = true;
                d+=t[i];
            }
        }
        cin >> M2;
        for(int i = 1; i <= M2; ++i){
            int d; cin >> d;
            for(int i = n; d<=T && i >= 2; --i){
                has_edge[d][i][1] = true;
                d+=t[i-1];
            }
        }
        return true;
    }
    void run(){
        kcase = 0;
        while(readInput()){
            for(int i = 1; i < n; ++i){
                dp[T][i] = INF;
            }
            dp[T][n] = 0;
            for(int i = T - 1; i >= 0; --i){
                for(int j = 1; j <= n; ++j){
                    dp[i][j] = dp[i + 1][j] + 1;
                    if(j > 1 && has_edge[i][j][1] && i + t[j - 1] <= T){
                        //cerr << i << " " << j << " " << has_edge[i][j][1] << endl;
                        //cerr << dp[i][j] << endl;
                        dp[i][j] = min(dp[i][j], dp[i + t[j - 1]][j - 1]);
                    }
                    if(j < n && has_edge[i][j][0] &&i + t[j] <= T){
                        //cerr << i << " " << j << " " << has_edge[i][j][1] << endl;
                        //cerr << dp[i][j] << endl;
                        dp[i][j] = min(dp[i][j], dp[i + t[j]][j + 1]);
                    }
                }
            }
            cout << "Case Number " << ++kcase << ": ";

            if(dp[0][1] >= INF){
                cout << "impossible" << endl;
            }else{
                cout << dp[0][1] << "\n";
            }
        }
    }
}

int main(){
    Solution::run();
    return 0;
}
