#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <set>
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

using l_int = long long;



int main() {
    int T; cin >> T;
    while(T--){
        l_int N, M; cin >> N >> M;
        vector<l_int> s;
        s.push_back(0);
        for(l_int i = 0; i < N; ++i){
            l_int t; cin >> t;
            s.push_back((s.back() + t)%M);
            //cerr << s.back() << " ";
        }
        //cerr << endl;
        set<l_int> p;
        l_int cur_max = numeric_limits<l_int>::min();
        for(l_int i = 1; i < N+1; ++i){
            p.insert(s[i-1]);
            auto t1 = p.upper_bound(s[i]);
            if(t1!=p.end()){
                //cerr << "t1: "  << *t1 << " i: "<< i << endl;
                l_int new_sum = (s[i] - *t1 + M)%M;
                //cerr << new_sum << endl;
                cur_max = cur_max < new_sum ? new_sum : cur_max;
            }
            cur_max = cur_max < s[i] ? s[i] : cur_max;
        }
        cout << cur_max << endl;


    }
    return 0;
}

