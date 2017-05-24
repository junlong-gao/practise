#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
using l_int = long long;

int main() {
    int T; cin >> T;
    while(T--){
        int N; cin >> N;
        vector<int> a;
        int sum_front = 0, sum_back = 0;
        for(int i = 0; i < N; ++i){
            int t; cin >> t;
            a.push_back(t);
            sum_back += t;
        }
        a.push_back(0);
        bool no = true;
        sum_back -= a[0];
        for(int i = 0; i <= N; ++i){
            if(sum_front == sum_back){
                no = false;
                cout << "YES" << endl;
                break;
            }else{
                sum_back -= a[i+1];
                sum_front += a[i];
            }
        }
        if(no)
            cout << "NO" << endl;
    }
    return 0;
}

