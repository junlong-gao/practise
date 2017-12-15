#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits>

namespace Solution{
    using namespace std;
    const int maxn = 5000 + 5;
    const int INF = 1000000;
    char p[maxn], q[maxn];
    int sp[26], sq[26], ep[26], eq[26];
    int dp[2][maxn], l[maxn][maxn];
    int n, m;

    void readInput(){
        scanf("%s%s", p, q);
        n = strlen(p); m = strlen(q);
        memset(sp, INF, sizeof(sp));
        memset(ep, -1, sizeof(ep));
        memset(sq, INF, sizeof(sq));
        memset(eq, -1, sizeof(eq));

        for(int i = 0; i < n; ++i){
            sp[p[i] - 'A']= min(i, sp[p[i] - 'A']);
            ep[p[i] - 'A'] = i;
        }
        for(int i = 0; i < m; ++i){
            sq[q[i] - 'A'] = min(i, sq[q[i] - 'A']);
            eq[q[i] - 'A'] = i;
        }
        memset(l,0,sizeof(int)* (n+1)*(m+1));
        l[0][0] = 0;
        for(int i = 0; i <= n; ++i){
            if(i){
                l[i][0] = l[i-1][0];
                int chr = p[i - 1] - 'A';
                if(sp[chr] == i - 1){ l[i][0]++; }
                if(ep[chr] == i - 1 && eq[chr] <  0){ l[i][0]--; }
            }
            for(int j = 0; j <= m; ++j){
                if(j){
                    l[i][j] = l[i][j-1];
                    int chr = q[j - 1] - 'A';
                    if(sq[chr] == j - 1 && sp[chr] > i - 1){ l[i][j]++; }
                    if(eq[chr] == j - 1 && ep[chr] <= i - 1){ l[i][j]--; }
                }
            }
        }
        /*
        for(int i = 0; i < n; ++i){
            for(int j =0; j < m ;++j){
                cerr << l[i][j] << " ";
            }
            cerr << endl;
        }
        */
    }

    
    void run(){
        int T; cin >> T;
        while(T--){
            readInput();
            dp[n][m] = 0;
            int t = 0;
            for(int i = n; i >=0; i--){
                for(int j = m; j >=0; j--){
                    int d1, d2; d1=d2=INF;
                    if(i+1<=n) d1=dp[t^1][j] + l[i+1][j];
                    if(j+1<=m) d2=dp[t][j+1] + l[i][j+1];
                    if(i==n&&j==m) dp[t][j] = 0;
                    else dp[t][j] = min(d1,d2);
                }
                t ^= 1;
            }
            printf("%d\n", dp[t^1][0]);        
        }


    }
}

int main(){
    Solution::run();
    return 0;
}
