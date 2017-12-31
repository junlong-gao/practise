#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#ifndef DEBUG
#define DEBUG 0
#endif
#define FILENAME "test.txt"
#include <fstream>
using namespace std;


int main() {
    ifstream in(FILENAME);
    if(DEBUG){
        cin.rdbuf(in.rdbuf());
    }

    int T; cin >> T;
    while(T--){
        int N, M; cin >> N >> M;
        vector<int> d(N, -1);
        vector<bool> visited(N, false);
        vector<vector<int>> edges(N);
        for(int i = 0; i < M; ++i){
            int u, v; cin >> u >> v;
            u--;v--;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        int s; cin >> s; --s;
        deque<int> q;
        q.push_back(s);
        visited[s] = true;
        d[s] = 0;
        while(!q.empty()){
            int top = q.front();
            q.pop_front();
            for(auto& it : edges[top]){
                if(!visited[it]){
                    visited[it] = true;
                    d[it] = d[top] + 6;
                    q.push_back(it);
                }
            }
        }
        for(auto& it : d){
            if(it) cout << it << " ";
        }
        cout << endl;
    }
    return 0;
}

