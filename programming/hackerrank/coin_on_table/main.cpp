#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

using l_int = long long;

int n, m, t;
const int infty = numeric_limits<int>::max(); 


//this is an example of dp of memorization
int search(vector<vector<char>>& map, 
            int x, int y, int k,
            vector<vector<vector<int>>>& dp){
    //boundary condition:
    if(k < 0 || x < 0 || x >= n || y < 0 || y >= m)
        return infty;
    if(map[x][y] == '*'){ //cerr << "find * " << x << " " << y << endl;
        return 0;
    }
    //special symbol for memorization
    if(dp[x][y][k] != -2)
        return dp[x][y][k];

    //recursive calculation
    int cur = infty;
    auto rst = search(map, x, y+1, k-1, dp);
    if(rst!=infty) rst += (map[x][y] == 'R')? 0: 1;
    cur = min(cur, rst);

    rst = search(map, x + 1, y, k-1, dp);
    if(rst!=infty) rst += (map[x][y] == 'D')? 0: 1;
    cur = min(cur, rst);

    rst = search(map, x - 1, y, k-1, dp);
    if(rst!=infty) rst += (map[x][y] == 'U')? 0: 1;
    cur = min(cur, rst);

    rst = search(map, x, y - 1, k-1, dp);
    if(rst!=infty) rst += (map[x][y] == 'L')? 0: 1;
    cur = min(cur, rst);
    dp[x][y][k] = cur;
    //cerr << x << " " << y << " " <<  k << " " << cur << endl;
    return cur;

}


int main() {
    cin >> n >> m >> t;
    vector<vector<char>> map(n,vector<char>(m));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            char c; cin >> c;
            map[i][j] = c;
        }
    }
    vector<vector<vector<int>>> dp(n,vector<vector<int>>(m, vector<int>(t + 1,-2)));
    auto rst =search(map, 0, 0, t, dp); 
    rst = rst == infty ? -1 : rst;
    cout <<   rst << endl;
    return 0;
}

