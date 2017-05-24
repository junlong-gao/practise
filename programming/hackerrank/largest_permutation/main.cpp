#include <cmath>
#include <utility>
#include <map>
#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
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
#define forn(i,s,n) for (int i = s; i < (int) (n); ++i)
#define min(x,y) ((x < y) ? (x) : (y))
#define fora(ele, container) for (auto& ele: (container))
#define readlist(list, n) for(int i = 0; i < (int)(n); ++i){int c; cin>>c; list.push_back(c);}
#define input(t) int t; cin >> t;
#define all(x) x.begin(), x.end()
#define vi vector<int> 
#define pp pair<int, int>
#define xx first
#define yy second
const ll inf = 1000000000000000000LL;

struct team_less{
    bool operator()(const int l, const int r){
        return l > r;
    }
};

int main() {
    ifstream in(FILENAME);
    if(DEBUG){
        cin.rdbuf(in.rdbuf());
    }
    ll N, K; cin >> N >> K;
    K = min(K,N);
    vector<int> l, x, y(N);
    forn(i,0, N){
        int t; cin >> t;
        l.push_back(t);
        x.push_back(i);
    }
    if( K >= N - 1){
        sort(l.begin(), l.end(),
                [&](const int lhs, const int rhs){
                    return lhs > rhs;
            });
    }else {
        sort(x.begin(), x.end(),
                [&](const int lhs, const int rhs){
                    return l[lhs] > l[rhs];
            });
        forn(i, 0, N){
            y[x[i]] = i;
        }
        forn(i, 0, N){
            if(x[i] != i){
                K--;
                int pos = x[i];
                swap(l[i], l[pos]);
                int rank = y[i];
                swap(x[i], x[rank]);
                swap(y[i], y[pos]);
            }
            if(K == 0) break;
        }
    }
    forn(i, 0, N){
        cout << l[i] << " " ;
    }
    return 0;
}

