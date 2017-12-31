#include <iostream>
#include <vector>
#include <algorithm>

namespace Solution{
    using ll = long long;
    using namespace std;
    vector<int> books;
    int n, k;
    ll tot, maxs;


    void readInput(){
        cin >> n >>k;
        tot = 0; maxs = 0;
        for(int i = 0; i < n; ++i){
            int t; cin >> t;
            books.push_back(t);
            tot += t;
            maxs = maxs > t? maxs: t;
        }
    }

    ll split(ll x){
        for(int i = 0; i < n; ++i){
            
        }

    }
    
    void run(){

    }

}
