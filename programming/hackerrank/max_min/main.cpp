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
#define forn(i,n) for (int i = 0; i < (int) (n); ++i)
#define min(x,y) ((x < y) ? (x) : (y))
#define fora(ele, container) for (auto& ele: (container))
#define all(x) x.begin(), x.end()
#define readlist(list, n) for(int i = 0; i < (int)(n); ++i){int c; cin>>c; list.push_back(c);}
#define vi vector<int> 
#define pp pair<int, int>;
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
    int N, K; cin >> N >> K;
    vector<int> list;
    readlist(list,N);
    sort(all(list));
    ll cur_min = inf;
    forn(i, N-K+1){
        if(list[i+K-1] - list[i] < cur_min)
            cur_min = list[i+K-1] - list[i];
    }
    cout << cur_min << endl;

    return 0;
}

