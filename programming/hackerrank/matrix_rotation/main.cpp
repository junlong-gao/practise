#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
using l_int = long long;


int main() {
    int M,N,R;  cin >> M >> N >> R;
    vector<vector<l_int>> a(M);
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            l_int t; cin >> t;
            a[i].push_back(t);
        }
    }
    int size = (min(M,N) + 1 )/2;
    vector<vector<l_int>> b(size);
    for(int offset = 0; offset < size; offset++){
        for(int j = offset; j < N - 1 -offset; ++j){
            b[offset].push_back(a[offset][j]);
        }
        for(int i = offset; i < M-1-offset; ++i){
            b[offset].push_back(a[i][N - 1 - offset]);
        }
        for(int j = N-1-offset; j > offset; --j){
            b[offset].push_back(a[M-1-offset][j]);
        }
        for(int i = M-1-offset; i > offset; --i){
            b[offset].push_back(a[i][offset]);
        }
    }
    for(int offset = 0; offset < size; offset++){
        int rotation = R % b[offset].size();
        rotate(b[offset].begin(), b[offset].begin()+rotation, b[offset].end());
    }

    for(int offset = 0; offset < size; offset++){
        auto it = b[offset].begin();
        for(int j = offset; j < N - 1 -offset; ++j){
            a[offset][j] = *it; ++it;
        }
        for(int i = offset; i < M-1-offset; ++i){
            a[i][N - 1 - offset] = *it;++it;
        }
        for(int j = N-1-offset; j > offset; --j){
            a[M-1-offset][j] = *it;++it;
        }
        for(int i = M-1-offset; i > offset; --i){
            a[i][offset] = *it;++it;
        }
    }

    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            cout << a[i][j] <<" ";
        }
        cout << endl;
    }
    return 0;
}

