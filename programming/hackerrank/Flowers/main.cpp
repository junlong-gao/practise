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
    int N, K; cin >> N >> K;
    int w = 0;
    int i = 0;
    vector<int> l;
    readlist(l, N);
    sort(all(l), [&](const int lhs, const int rhs){
            return lhs > rhs;
    });
    int result = 0;
    while(1){
        int j = 0;
       while(j < K && i < N){
           result += (w+1)*l[i];
           j++;i++;
       }
       if(j < K) break;
       else w++;
    }
    cout << result;
    return 0;
}

