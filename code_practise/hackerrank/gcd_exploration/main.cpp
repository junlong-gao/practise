#include <cmath>
#include <utility>
#include <map>
#include <cstdio>
#include <vector>
#include <deque>
#include <queue>
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
#define forn(i,s,n) for (int i = s; i < (int) (n); ++i)
#define min(x,y) ((x < y) ? (x) : (y))
#define fora(ele, container) for (auto& ele: (container))
#define readlist(list, n) for(int i = 0; i < (int)(n); ++i){int c; cin>>c; list.push_back(c);}
#define input(t) int t; cin >> t;
#define all(x) x.begin(), x.end()
#define vi vector<int> 
#define pp pair<int, int>
#define xx first
#define yy second
const ll inf = 1000000000000000000LL;

struct team_less{
    bool operator()(const int l, const int r){
        return l > r;
    }
};

ll gcd(ll a, ll b){

    if(a < b){
        ll tmp; tmp = a;
        a = b; b = tmp;
    }
    ll gcd = b;
    while(b){
        gcd = b;
        b = a % b;
        a = gcd;
    }
    return gcd;
}

int main() {
    ifstream in(FILENAME);
    if(DEBUG){
        cin.rdbuf(in.rdbuf());
    }
    ll N, a, b; cin >> N >> a >> b;
    ll rep = gcd(a,b);
    while(rep--){
        cout << N;
    }


    return 0;
}

