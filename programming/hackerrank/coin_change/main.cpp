#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
int main(){
    int N, M;
    cin >> N >> M;
    vector<int> Ci;
    for(int i = 0; i < M; i++){
        int c;
        cin >> c;
        Ci.push_back(c);
    }

    vector<vector<long long>> S(2,vector<long long>(N+1));
    for(int n = 0; n <= N; ++n){
        S[0][n] = (n%Ci[0]==0);
    }
    for(int i = 0; i < M; ++i){
        S[i%2][0] = 1;
    }
    for(int i = 1; i < M; ++i){
        for(int n = 1; n <= N; ++n){
            S[i%2][n] = S[(i-1)%2][n];
            if(n - Ci[i] >= 0) S[i%2][n] += S[i%2][n - Ci[i]];
        }
    }
    cout << S[(M - 1)%2][N] << endl;

}
