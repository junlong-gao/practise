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
    int N, M; cin >> N >> M;
    vector<vector<unsigned>> edges(N, vector<unsigned>(N, -1));
    vector<int> unvisited;
    for(int i = 0; i < N; ++i){
        unvisited.push_back(i);
    }
    for(int i = 0; i < M; ++i){
        int u, v; cin >> u >> v;
        u--; v--;
        int w; cin >> w;
        edges[u][v] = edges[v][u] =  w;
    }
    int r; cin >> r; r--;
    vector<unsigned> key(N, -1);
    key[r] = 0;
    unsigned sum = 0;
    while(!unvisited.empty()){
        unsigned min = -1;
        int index = -1;
        for(int i = 0; i < (int)unvisited.size(); ++i){
            int it = unvisited[i];
            if(key[it] < min){
                index = i;
                min = key[it];
            }
        }
        sum += min;
        int cur = unvisited[index];
        swap(unvisited[index], unvisited.back());
        unvisited.pop_back();
        for(int i = 0; i < (int) unvisited.size(); ++i){
            int it = unvisited[i];
            if(edges[it][cur] < key[it]){
                key[it] = edges[it][cur];
            }
        }
    }
    cout << sum << endl;

    return 0;
}

