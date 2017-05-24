#include <cmath>
#include <deque>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class coor{
public:
    int x, y;
    coor(int _x, int _y): x(_x), y(_y){;}
    coor(): x(0), y(0){;}
    bool operator==(const coor& other) const {
        return x == other.x && y == other.y;
    }
};
static int adj_x[4] = {-1,0,0,1};
static int adj_y[4] = {0,-1,1,0};

int main() {
    int T; cin >> T;
    while(T--){
        int N, M; cin>>N>>M;
        vector<vector<char>> map(N,vector<char>(M, '.'));
        vector<vector<int>> p(N,vector<int>(M, '.'));
        vector<vector<bool>> visited(N,vector<bool>(M, false));
        coor s, e;
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                char c; cin >> c;
                map[i][j] = c;
                if(c == 'M'){
                    s.x = i; s.y = j;
                }
                if(c == '*'){
                    e.x = i; e.y = j;
                }
            }
        }
        vector<coor> q;
        q.push_back(s);
        visited[s.x][s.y] = true;
        int counter = 0;
        while(!q.empty()){
            auto t = q.back();
            q.pop_back();
            if(map[t.x][t.y] == '*') break;
            for(int i = 0; i < 4; ++i){
                int n_x = t.x + adj_x[i];
                int n_y = t.y + adj_y[i];
                if((n_x >=0 && n_x < N) &&
                    (n_y >= 0 && n_y < M)&&
                    (visited[n_x][n_y] == false) &&
                    (map[n_x][n_y] != 'X')){
                    q.emplace_back(n_x,n_y);
                    visited[n_x][n_y] = true;
                    p[n_x][n_y] = 3 - i;
                }
            }
        }
        while(1){
            int prev = p[e.x][e.y];
            e.x += adj_x[prev];
            e.y += adj_y[prev];
            int choice = 0;
            for(int i = 0; i < 4; ++i){
                int n_x = e.x + adj_x[i];
                int n_y = e.y + adj_y[i];
                if((n_x >=0 && n_x < N) &&
                    (n_y >= 0 && n_y < M)&&
                    (map[n_x][n_y] != 'X')){
                    choice++;
                }
            }
            if(choice > 2 || (choice == 2 && s==e)){
                counter++;
            } 
            if(s==e) break;
        }
        int K; cin >> K;

        if(K==counter){
            cout << "Impressed" <<endl;
        }else{
            cout << "Oops!" <<endl;
        }




    }
    return 0;
}

