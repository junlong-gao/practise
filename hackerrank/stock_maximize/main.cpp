#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main(){
    int T;
    cin >> T;
    while(T > 0){
        T--;
        int N;
        cin >> N;
        vector<long long> price;
        for(int i = 0; i < N; ++i){
            int p;
            cin >> p;
            price.push_back(p);
        }
        long long max = -1;
        long long profit = 0;
        for(int j = N - 1; j >=0; --j){
            //a greedy choice by travel back in time:
            //the opt solution at time i, if it is
            // a local max from i to end, it must be 
            // a sell
            if(price[j] > max) max = price[j];
            else profit += max - price[j];
        }
        cout << profit << "\n";
    }
    
}
