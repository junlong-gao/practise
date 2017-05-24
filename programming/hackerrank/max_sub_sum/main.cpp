#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

using l_int = long long;
l_int max(const l_int a, const l_int b){
    return a> b? a:b;
}
int main() {

    int T; cin >> T;
    while(T){
        T--;
        int N; cin >> N;
        vector<int> a;
        for(int i = 0; i < N; ++i) {
            int t; cin >> t;
            a.push_back(t);
        }
        vector<l_int> dp(N+1);
        dp[0] = 0;
        vector<l_int> sum(N+1);
        for(int i = 1; i <= N; ++i){
            dp[i] = max(dp[i-1] + a[i-1], a[i-1]);
            if(i == 1) sum [i] = a[i-1];//dirty boundarty
            else sum[i] = max(max(sum[i-1]+a[i-1],sum[i-1]), a[i-1]);
        }
        l_int max = dp[1];
        for(int i = 1; i <=N; ++i){
            if(dp[i] > max) max = dp[i];
        }
        cout << max << " ";
        //cerr << endl;
        max = sum[1];
        for(int i = 1; i <=N; ++i){
          //  cerr << sum[i] << " ";
            if(sum[i] > max) max = sum[i];
        }
        //cerr << endl;
        cout << sum[N] << endl;
    }
    return 0;
}
