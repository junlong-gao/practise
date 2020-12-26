//
//  Solution.hpp
//  practise
//
//  Created by Junlong Gao on 7/30/16.
//  Copyright © 2016 Junlong Gao. All rights reserved.
//

#ifndef Solution_hpp
#define Solution_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class NumMatrix {
    vector<vector<int>> tree;
    vector<vector<int>>& nums;
public:
    NumMatrix(vector<vector<int>> &matrix):nums(matrix){
        if(matrix.size() < 1) return;
        tree.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1));
        for(int x = 0; x < matrix.size(); ++x){
            for(int y = 0; y < matrix[0].size(); ++y){
                add(x, y, matrix[x][y]);
            }
        }

    }

    void update(int row, int col, int val){
        int diff = val - nums[row][col];
        nums[row][col] = val;
        add(row, col, diff);
    }

    void add(int row, int col, int diff) {
        int x = row + 1;
        while(x < tree.size()){
            int y = col + 1;
            while(y < tree[x].size()){
                tree[x][y] += diff;
                y += y & (-y);
            }
            x += x & (-x);
        }
    }

    int sum(int row, int col){
        int ret = 0;
        int x = row + 1;
        while(x > 0){
            int y = col + 1;
            while(y > 0){
                ret += tree[x][y];
                y -= y & (-y);
            }
            x -= x & (-x);
        }
        return ret;
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int big = 0, small = 0, left = 0, right = 0;
        if(row2 >= 0 && col2 >=0) big = sum(row2, col2);
        if(row1-1>=0 && col1-1>=0) small = sum(row1 - 1, col1-1);
        if(col1 - 1>=0) left = sum(row2, col1 -1);
        if(row1 - 1 >= 0) right = sum(row1 -1 , col2);
        return big - left - right + small;
    }
};


// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.update(1, 1, 10);
// numMatrix.sumRegion(1, 2, 3, 4);
#endif /* Solution_hpp */
