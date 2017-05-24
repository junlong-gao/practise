#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

using l_int = long long;
int main() {
    int T; cin >> T;
    while(T > 0){
        T--;
        int N; cin >> N;
        vector<l_int> bricks;
        for(int i = 0; i < N; ++i){
            int b; cin >> b;
            bricks.push_back(b);
        }
        vector<l_int> dp1(N+1, 0);
        vector<l_int> dp2(N+1, 0);
        for(int i = 1; i <=N; ++i){
            l_int max = -1;
            l_int cummulator = 0;
            for(int j = 1; j <= 3; j ++){
                if(j > i) break;
                cummulator += bricks[N - i + (j-1)];
                if(dp2[i-j] + cummulator >= max )
                    max =dp2[i-j] + cummulator; 
            }
            dp1[i] = max;

            l_int min = 0x0FFFFFFFFFFFFFFF;
            cummulator = 0;
            for(int j = 1; j <= 3; j ++){
                if(j > i) break;
                if(dp1[i-j] <= min )
                    min =dp1[i-j]; 
            }
            dp2[i] = min;
        }
        cout << dp1[N] << "\n";
    }
    return 0;
}
