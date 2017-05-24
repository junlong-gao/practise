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
#define all(x) x.begin(), x.end()
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
    int N; cin >> N;
    vector<int> h;
    forn(i,0,N){
        int t; cin >> t;
        h.push_back(t);
    }
    vector<int> b(N);
    b[0] = (h[N-1] + 1) /2;
    forn(i,1,N){
        b[i] = (b[i-1] + h[N-1-i] + 1) / 2; 
    }
    cout << b.back();
    


    
    return 0;
}

