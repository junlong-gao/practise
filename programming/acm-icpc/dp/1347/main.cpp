#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>

namespace Solution{
    using namespace std;
    const int maxn = 50 + 5;
    double dp[maxn][maxn], dist[maxn][maxn];
    int n,x[maxn], y[maxn];


    void readInput(){
        for(int i = 1; i <= n; ++i){
            cin >> x[i] >> y[i];
        }
        for(int i = 1; i <= n; ++i){
            for(int j = 1; j <=n; ++j){
                double dx = x[i] - x[j];
                double dy = y[i] - y[j];
                dist[i][j] = sqrt(dx*dx + dy*dy);
            }
        }
        memset(dp, 0, sizeof(dp));
        for(int j = 1; j <= n-2; ++j){
            dp[n-1][j] = dist[n-1][n] + dist[n][j];
        }
    }

    
    void run(){
        while(cin >> n){
            readInput();
            for(int i = n-2; i >= 2; --i){
                for( int j = 1; j < i; ++j){
                    double d1 = dist[i][i+1] + dp[i+1][j];
                    double d2 = dist[i+1][j] + dp[i+1][i];
                    dp[i][j] = min(d1, d2);
                }
            }
            printf("%.2lf\n", dp[2][1] + dist[1][2]);
        }

    }
}

int main(){
    Solution::run();
    return 0;
}
