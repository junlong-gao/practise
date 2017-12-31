#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
using l_int = long long;

int main() {
    int n, m; cin >> n;
    vector<int> a;
    for(int i = 0; i < n; ++i){
        int t; cin >> t;
        a.push_back(t);
    }
    vector<int> b;
    int table[202];
    for(int j = 0; j < 202; j++){
        table[j]=0;
    }
    cin >> m;
    int offset; cin >> offset;
    b.push_back(offset);
    table[101]++;
    for(int i = 1; i < m; ++i){
        int t; cin >> t;
        b.push_back(t);
        table[t-offset + 101]++;
    }
    for(int i = 0; i < n; ++i){
        table[a[i]-offset + 101]--;
    }
    for(int j = 0; j < 202; j++){
        if(table[j]) cout << j + offset - 101 << " ";
    }

    
    return 0;
}

