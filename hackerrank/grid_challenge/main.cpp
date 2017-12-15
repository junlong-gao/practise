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
    int T; cin >> T;
    while(T--){
        int N; cin >> N;
        vector<vector<int>> grid(N, vector<int>(N, 'c'));
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                char c; cin >> c;
                grid[i][j] = c;
            }
        }
        for(int i = 0; i < N; ++i){
            sort(grid[i].begin(), grid[i].end());
        }
        bool yes = true;
        for(int j = 0; j < N; ++j){
            for(int i = 0; i+1 < N; ++i){
                if(grid[i][j] > grid[i+1][j]){
                    yes = false;
                    break;
                }
            }
        }
        if(yes){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
    return 0;
}

