#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <numeric>
#ifndef DEBUG
#define DEBUG 0
#endif
#define FILENAME "test.txt"
#include <fstream>
using namespace std;
using ll = long long;
#define forn(i,n) for (int i = 0; i < (int) n; ++i)
#define fora(ele, container) for (auto& ele: container)
#define pp pair<int, int>;
const ll inf = 1000000000000000000LL;
const ll MOD = 1000000007LL;

class c{
public:
    ll cost; 
    bool hori;
    c(ll _cost, bool _hori):cost(_cost), hori(_hori){;}
};

//observation: if we have a sequence of solution ,then
//if two consecutive cut is different direction, we can
//always arrange them in such a way that cost is decreaing
//to obtain a better total cost (local optimal structure)
//
//also the moduli must be taken even in addition (don't use +=)
//
int main() {
    ifstream in(FILENAME);
    if(DEBUG){
        cin.rdbuf(in.rdbuf());
    }
    int T; cin >> T;
    while(T--){
        int M, N; cin >> M >> N;
        vector<c> costs;
        forn(i, M-1){
            ll t; cin >> t;
            costs.emplace_back(t, true);
        }
        forn(i, N-1){
            ll t; cin >> t;
            costs.emplace_back(t, false);
        }
        sort(costs.begin(), costs.end(), 
                [&](const c& c1, const c& c2){
                return c1.cost > c2.cost;
            });
        ll H, V; H = V = 0;
        ll sum = 0;
        forn(i, M+N-2){
            if(costs[i].hori){
                sum = (sum + ((V+1) * costs[i].cost) % MOD) % MOD;
                ++H;
            }else{
                sum = (sum + ((H+1) * costs[i].cost) % MOD) % MOD;
                ++V;
            }
        }
        cout << sum << endl;

    }
    return 0;
}

