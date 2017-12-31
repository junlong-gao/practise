#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
vector<int> a;

int main() {
    int n; cin >> n;
    for(int i = 0; i < n; ++i){
        int t; cin >> t;
        a.push_back(t);
    }
    sort(a.begin(), a.end());
    int m = n / 2;
    if(a.size() % 2){
        cout << a[m] << endl;
    }else{
        cout << (a[m] + a[m-1])/2 << endl;
    }
    return 0;
}

