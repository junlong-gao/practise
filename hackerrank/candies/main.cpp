#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#ifdef DEBUG
#define DEOUT(name,x) do { std::cerr << name << " : " << x << endl; } while (0)
#else 
#define DEOUT(name,x)
#endif
using namespace std;
using l_int = long long;

int main() {
    int N; cin >> N;
    vector<int> rates;
    for(int i = 0; i < N; ++i){
        int rate; cin >> rate;
        rates.push_back(rate);
    }
    vector<int> candies(N,1);
    int counter = 1;
    for(int i = 0; i + 1 < N; ++i){
        if(rates[i]<rates[i+1])
            candies[i+1] = ++ counter;
        else counter = 1;
        DEOUT(i+1, candies[i+1]);
    }
    counter = 1;
    for(int i = N-1; i - 1 >=0; --i){
        if(rates[i] < rates[i-1])
            candies[i-1] = max(candies[i-1],++counter);
        else counter = 1;
        DEOUT(i-1, candies[i-1]);
    }
    l_int sum = 0;
    for(int i = 0; i < N; ++i){
        sum+=candies[i];
        DEOUT(i, candies[i]);
    }
    cout << sum << endl;
    return 0;
}
