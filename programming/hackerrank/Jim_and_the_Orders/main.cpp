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
    input(N);
    vector<int> list;
    vector<int> order;
    forn(i, 0, N){
        int t, d; cin >> t>>d;
        list.push_back(t+d);
        order.push_back(i+1);
    }
    sort(all(order), [&](const int lhs, const int rhs){
            if(list[lhs - 1] < list [rhs - 1]) return true;
            if(list[lhs - 1] == list[rhs -1] && lhs < rhs) return true;
            return false;
    });
    forn(i, 0, N){
        cout << order[i] << " ";
    }
    return 0;
}

