#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

static bool grid[10][10];
static bool visited[10][10];
static int n,m;
const static int adj_x[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
const static int adj_y[8] = {-1,  0,  1, -1, 1, -1, 0, 1};

class coor{
public:
    int x; int y;
    coor(int _x, int _y):x(_x),y(_y){;}
};

bool checkValid(int x, int y){
    if(x >= m || x < 0) return false;
    if(y >= n || y < 0) return false;
    if(visited[x][y]) return false;
    if(!grid[x][y]) return false;
    return true;
}

int DFS_count(int x, int y){
    int counter = 0;
    vector<coor> s;
    visited[x][y] = true;
    grid[x][y] = false;
    s.emplace_back(x,y);
    while(!s.empty()){
        int _x = s.back().x;
        int _y = s.back().y;
        s.pop_back(); counter++;
        for(int i = 0; i < 8; ++i){
            int nx = _x + adj_x[i];
            int ny = _y + adj_y[i];
            if(checkValid(nx,ny)){
                visited[nx][ny] = true;
                grid[nx][ny] = false;
                s.emplace_back(nx,ny);
            }
        }
    }
    return counter;
}

int main() {
    cin >> m >> n;
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            int t; cin >> t;
            if(t) grid[i][j] = true;
            else grid[i][j] = false;
            visited[i][j] = false;
        }
    }
    int max = -1;
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            if(checkValid(i,j)){
                int t = DFS_count(i,j);
                if(t > max) max = t;
            }
        }
    }

    cout << max << endl;
    return 0;
}

