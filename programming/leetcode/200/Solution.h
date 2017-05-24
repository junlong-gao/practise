//
// Created by Junlong Gao on 7/30/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include<vector>

using namespace std;

class Solution {
    using grid_t = vector<vector<char>>;
    using mask_t = vector<vector<bool>>;
    bool isValid(int x, int y, grid_t& grid){
        if(x < 0 or x >= grid.size()) return false;
        if(y < 0 or y >= grid[0].size()) return false;
        if(grid[x][y] == '0') return false;
        return true;
    }
    const int dx[4] = {0, -1, 0, 1};
    const int dy[4] = {1, 0, -1, 0};
    void fill(grid_t& grid, int i, int j){
        vector<pair<int, int>> s;
        s.push_back({i,j});
        grid[i][j] = '0';
        while(!s.empty()){
            auto cur = s.back();
            s.pop_back();
            for(int i = 0; i < 4; ++i){
                int x = cur.first + dx[i], y = cur.second + dy[i];
                if(isValid(x, y, grid)){
                    grid[x][y] = '0';
                    s.push_back({x,y});
                }
            }
        }
        return;
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int counter = 0;
        for(int i = 0; i < grid.size(); ++i){
            for(int j = 0; j < grid[0].size(); ++j){
                if(grid[i][j]=='1'){
                    fill(grid, i, j);
                    counter++;
                }
            }
        }
        return counter;
    }
};


#endif //PRACTISE_SOLUTION_H
