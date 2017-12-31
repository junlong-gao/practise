#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;
using l_int = long long;

int main() {
    l_int N,M;
    cin >> N >> M;
    vector<l_int> timestamp(N,0);
    for(int i = 0; i < M; ++i){
        l_int p,q; cin >> p >>q;
        --p;--q;
        l_int k; cin >> k;
        timestamp[p] += k;
        if(q < N) timestamp[q+1] += -k;
    }
    l_int sum = 0;
    l_int t_max = numeric_limits<l_int>::min();
    for(l_int i = 0; i < N; ++i){
        sum += timestamp[i];
        if(sum > t_max)
            t_max = sum;
    }
    cout << t_max <<endl;
    return 0;
}

