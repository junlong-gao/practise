#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

namespace Solution{
    using namespace std;
    const int maxn = 30 + 5;
    int n, d[maxn][3], blocks[maxn][3];

    void readInput(){
        for(int i = 0; i < n; ++i){
            cin >> blocks[i][0];
            cin >> blocks[i][1];
            cin >> blocks[i][2];
            sort(blocks[i], blocks[i] + 3);
        }
        memset(d, 0, sizeof(d));
    }

    void get_dimensions(int v[], int i, int j){
        int idx = 0;
        for(int k = 0; k < 3; k++){
            if(k!=j){
                v[idx++] = blocks[i][k];
            }
        }
    }

    int dp(int i,int j){
        int& ans = d[i][j];
        if(ans > 0) return ans;
        int v[2], vt[2];
        get_dimensions(v, i, j);
        for(int a = 0; a < n; ++a){
            for(int b = 0; b < 3; ++b){
                get_dimensions(vt, a, b);
                if(v[0] < vt[0] && v[1]<vt[1])
                    ans = max(ans, dp(a,b));
            }
        }
        ans += blocks[i][j];
        return ans;
    }
    
    void run(){
        int kcase = 0;
        while(cin >> n && n){
            readInput();
            int rst = 0;
            for(int i =0; i <n; ++i){
                for(int j =0; j < 3; ++j){
                    rst = max(rst, dp(i, j));
                }
            }
            printf("Case %d: maximum height = %d\n", ++kcase, rst);
        }
    }
}

int main(){
    Solution::run();
    return 0;
}
