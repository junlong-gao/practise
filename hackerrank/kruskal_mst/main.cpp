#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <iostream>
#include <numeric>
#include <algorithm>
#ifndef DEBUG
#define DEBUG 0
#endif
#define FILENAME "test.txt"
#include <fstream>
using namespace std;
class edge{
public:
    unsigned u, v, w;
    edge(unsigned _u, unsigned _v, unsigned _w)
        :u(_u),v(_v),w(_w){;}
};

class union_find{
public:
    vector<int> rank,p;
    int size;
    union_find(int _size):size(_size){
        p.resize(size);
        rank.resize(size);
        iota(p.begin(), p.end(), 0);
    }
    int trace(int x){
        int r = p[x];
        while(r!=p[r]) r = p[r];
        while(x!=r){
            int y = p[x];
            p[x] = r;
            x = y;
        }
        return r;
    }
    bool find(int x, int y){
        return trace(x) == trace(y);
    }
    void union_set(int x, int y){
        int r1 = trace(x);
        int r2 = trace(y);
        if(rank[r1] > rank[r2]){
            p[r2] = r1;
        }else{
            p[r1] = r2;
            if (rank[r1] == rank[r2])
                rank[r2] ++;
        }
    }
};

int main() {
    ifstream in(FILENAME);
    if(DEBUG){
        cin.rdbuf(in.rdbuf());
    }

    int N, M; cin >> N >> M;
    vector<edge> edges;
    for(int i = 0; i < M; ++i){
        int u, v, w; cin >> u >> v>> w;
        u--; v--;
        edges.emplace_back(u,v,w);
    }
    sort(edges.begin(), edges.end(), 
            [&](const edge& e1, const edge& e2){
            return e1.w < e2.w;
    });
    union_find s(N);
    int sum = 0;
    for(auto &it : edges){
        if(!s.find(it.u, it.v)){
            sum += it.w;
            s.union_set(it.u, it.v);
        }
    }
    cout << sum << endl;

    return 0;
}

