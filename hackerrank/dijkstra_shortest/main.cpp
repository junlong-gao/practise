#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main(){
    int T;
    cin >> T;
    while(T>0){
        T--;
        int N, M;
        cin >> N >> M;
        vector<int> d(N, 999);
        vector<bool> k(N);
        vector<vector<pair<int,int>>> edges(N);
        for(int i = 0; i < M; ++i){
            int x, y, r;
            cin >> x >> y >> r;
            x--; y--;
            edges[x].emplace_back(make_pair(y,r));
            edges[y].emplace_back(make_pair(x,r));
        }
        int S; cin >> S;
        S--;
        d[S] = 0;
        for(int i = 0; i < N; ++i){
            int min = 999, mini = -1;
            for(int j = 0; j < N; ++j){
                if(!k[j]&&d[j]< min){
                    mini = j; min = d[j];
                }
            }
            if(mini < 0){
                break;
            }
            k[mini]  = true;
            for(int j = 0; j < (int)edges[mini].size(); ++j){
                int u =edges[mini][j].first;
                int w =edges[mini][j].second;
                if(!k[u] && 
                d[mini]+ w <d[u])
                d[u]=d[mini]+w;
            }
        }
        for(int i = 0; i < (int)d.size(); ++i){
            if(i!=S) cout << (d[i] == 999? -1:d[i]) << " ";
        }
        cout << endl;

    }
    return 0;
}
