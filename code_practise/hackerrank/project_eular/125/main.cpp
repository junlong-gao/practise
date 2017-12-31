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
#include <sstream>
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

bool isPalindromic(int num){
    stringstream ss;
    ss << num;
    string s(ss.str());
    for(int i = 0; i < ((int)s.length() + 1) / 2; ++i){
        if(s[i] != s[s.length() - 1 - i]) return false;
    }
    return true;
}

int main() {
    ifstream in(FILENAME);
    if(DEBUG){
        cin.rdbuf(in.rdbuf());
    }
    int T; cin >> T;
    while(T--){
        ll N, d; cin >> N >> d;
        int upper = sqrt(N);
        vector<int> so_far;
        ll result = 0;
        for(int i = 1; i < upper; ++i){
            ll sum = i * i;
            for(int j = i + d; j < upper; j = j + d){
                sum += j * j;
                if(sum < N && 
                    isPalindromic(sum) && 
                    find(so_far.begin(), so_far.end(), sum) == so_far.end()){
                        //cerr << sum << endl;
                        so_far.push_back(sum);
                        result += sum;
                }
            }
        }
        cout << result << endl;
    }
    return 0;
}

