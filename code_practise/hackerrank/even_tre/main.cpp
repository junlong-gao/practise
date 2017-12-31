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

int ans = 0;
int n, m;
vector<vector<int>> edges; 
vector<bool> visited;

int dfs(int node){
    int subtree_size = 0;
    forn(i, (int)edges[node].size()){
        int subtree = edges[node][i];
        if(!visited[subtree]){
            visited[subtree] = true;
            int tree_size = dfs(subtree);
            subtree_size += tree_size;
            ans += tree_size%2? 0:1;
        }
    }
    return subtree_size + 1;
}

int main() {
    ifstream in(FILENAME);
    if(DEBUG){
        cin.rdbuf(in.rdbuf());
    }
    cin >> n >> m;
    edges.resize(n); visited.resize(n);
    forn(i,m){
        int u, v; cin >> u >> v;
        u--;v--;
        edges[v].push_back(u);
    }

    int i = 0; while(edges[i].empty()) ++i; 
    visited[i] = true;
    dfs(i);
    cout << ans << endl;
    return 0;
}

