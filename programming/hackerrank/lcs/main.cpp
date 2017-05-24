#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;
using l_int = long long;

int main(){
    int N; vector<int> a;
    cin >> N;
    for(int i = 0; i < N; i++){
        int t; cin >> t;
        a.push_back(t);
    }
    vector<int> dp;
    for(int i = 0; i < N; ++i){
        auto it = lower_bound(dp.begin(), dp.end(),a[i]);
        if(it!=dp.end()) *it = a[i]; 
        else dp.push_back(a[i]);
    }
    cout<<dp.size()<<endl;
}

