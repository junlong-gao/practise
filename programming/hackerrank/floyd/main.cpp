#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;
const int INF = -1;
inline int min(int a, int b){
    if(a < 0) return b;
    else return a > b? b : a;
}

int main(){
    int N, M;
    cin >> N >> M;
    vector<vector<int>> D(N, vector<int>(N,INF));
    for(int i = 0; i < N; ++i ){
        D[i][i] = 0;
    }
    while(M > 0){
        M--;
        int x, y ,r;
        cin >> x >> y >> r;
        x--;y--;
        D[x][y] = r;
    }

    for(int k = 0; k < N;  ++k){
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                if(D[i][k]>=0 && D[k][j] >= 0)
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }

    int Q; cin >> Q;
    while(Q > 0){
        Q--;
        int x, y;
        cin >> x >> y;
        x--;y--;
        cout << (int)D[x][y] << "\n";
    }

    return 0;
}
