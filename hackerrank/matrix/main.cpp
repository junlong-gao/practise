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


//observation: evetuntually all cities of machine
//and its reachable cities will form a collection of
//disjoint sets. The idea is to greedily add largest weight
//edges to each of disjoint sets, unless this edge will 
//connnet two cities of machine. 
//Thus we think of kruskal in reverse by:
//1. sort edges starting from the largest
//2. if an edge will connect two disjoint machine cites, this
//edge must be cutted, otherwise this is the LARGEST edge we can 
//safely added to one of our disjoint cities (depending on the endpoint
//of this edge)
//3. unite the non-machine city and the machine city via this edge,
//update the hasMachine attribute
//
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
class edge{
public:
    unsigned u, v, w;
    edge(unsigned _u, unsigned _v, unsigned _w)
        :u(_u),v(_v),w(_w){;}
};
int main() {
    ifstream in(FILENAME);
    if(DEBUG){
        cin.rdbuf(in.rdbuf());
    }
    int N; cin>> N;
    int k; cin >> k;
    vector<edge> edges;
    vector<bool> hasM(N, false);
    ll total = 0;
    forn(i, N - 1){
        int u,v,w; cin >> u>>v>>w;
        edges.emplace_back(u,v,w);
    }
    sort(edges.begin(), edges.end(), 
            [&](const edge& e1, const edge& e2){
            return e1.w > e2.w;
    });
    forn(i, k){
        int x; cin >> x;
        hasM[x] = true;
    }

    union_find s(N);
    total = 0;
    fora(ele, edges){
        int r1 = s.trace(ele.u);
        int r2 = s.trace(ele.v);
        if(r1!= r2 && (hasM[r1] && hasM[r2])){
            total += ele.w;
        } else {
            if(r1!=r2) s.union_set(r1, r2);
            if(hasM[r1] || hasM[r2]){
                hasM[r1] = hasM[r2] = true;
                hasM[ele.u] = hasM[ele.v] = true;
            }
        }
    }
    
    cout << total << endl;



    return 0;
}

