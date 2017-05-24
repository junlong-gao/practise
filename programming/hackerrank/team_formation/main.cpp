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
#define forn(i,n) for (int i = 0; i < (int) (n); ++i)
#define min(x,y) ((x < y) ? (x) : (y))
#define fora(ele, container) for (auto& ele: (container))
#define all(x) x.begin(), x.end()
#define vi vector<int> 
#define pp pair<int, int>;
const ll inf = 1000000000000000000LL;

// the more constrain, the easier to be greedy
// note in this problem, we wish to form as few
// team as possible, and the constrain shows that
// duplicated skill members are of particular importance
// in determine the number of team: if we have too many
// people with same skill level, a team of size 1 is 
// ineivable. We greedily form team by keeping adding x to
// team end in x-1 with the smallest size(this muti team is 
// due to the presence of duplicated skilled member), and
// we only add new team formation when we cannot place x (no team
// end in x-1)
// use a map for fast search and priority queue to maintain
// team size order
//
struct team_less{
    bool operator()(const int l, const int r){
        return l > r;
    }
};

int main() {
    ifstream in(FILENAME);
    if(DEBUG){
        cin.rdbuf(in.rdbuf());
    }
    int T; cin >>T;
    while(T--){
        int n; cin >> n;
        vector<int> team;
        forn(i, n){
            int r; cin >> r;
            team.push_back(r);
        }
        sort(all(team));
        map<int, priority_queue<int, vi, team_less>> sets;
        forn(i, n){
            auto it = sets.find(team[i] - 1);
            int size = 0;
            if(it!= sets.end()){
                if(it->second.size()){
                    size = it->second.top();
                    it->second.pop();
                }
            }
            sets[team[i]].push(size + 1);
        }
        ll cur_min = inf;
        fora(ele, sets){
            if(ele.second.size()) cur_min = min(ele.second.top(), cur_min);
        }
        if(cur_min >= inf) cur_min = 0;
        cout << cur_min << endl;
        


    }
    return 0;
}

