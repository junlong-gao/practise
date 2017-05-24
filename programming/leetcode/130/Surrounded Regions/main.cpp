//
//  main.cpp
//  Surrounded Regions
//
//  Created by John on 9/13/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <deque>
#include <vector>
#include <util.h>

using namespace std;

class Solution {
public:

    void solve(vector<vector<char>>& board) {
        auto height = board.size();
        if (height==0) {
            return;
        }
        auto width = board[0].size();
        if (width==0) {
            return;
        }
        for (auto i = 0; i<width; i++) {
            if (board[0][i]=='O') {
                BFS(board, 0,i);
            }
            if (board[height-1][i]=='O') {
                BFS(board, height-1,i);
            }
        }
        
        for (auto i = 0; i<height; i++) {
            if (board[i][0]=='O') {
                BFS(board, i,0);
            }
            if (board[i][width-1]=='O') {
                BFS(board, i,width-1);
            }
        }
        
        for (auto i = 0; i<height; i++) {
            for (auto j = 0; j<width; j++) {
                if (board[i][j]=='B') {
                    board[i][j]='O';
                } else if (board[i][j]=='O') {
                    board[i][j]='X';
                }
            }
        }
        
    }
    
    void BFS(vector<vector<char>>& board, unsigned long row, unsigned long col){
        auto height = board.size();
        auto width = board[0].size();
        int moves[4][2] = {{-1,0}, {0, 1}, {1, 0},{0,-1}};

        deque<pair<int, int>> q;
        board[row][col]='B';
        q.push_back(make_pair(row, col));
        
        
        while (!q.empty()) {
            auto it = q.front();
            q.pop_front();
            for (int l = 0; l<4; l++) {
                int nRow = it.first + moves[l][0];
                int nCol = it.second + moves[l][1];
                if (nRow < height &&
                    nCol < width &&
                    board[nRow][nCol]=='O') {
                    board[nRow][nCol] = 'B';
                    q.push_back(make_pair(nRow, nCol));
                }
            }
        }
    }
};

int main(int argc, const char * argv[]) {
    int height = 4;
    int width = 6;
    vector<vector<char>> board;
    
    
    for (int i = 0 ; i < height ; i++) {
        vector<char> tmp(width);
        board.push_back(tmp);
        for (int j = 0 ; j < width; j++) {
            board[i][j]='X';
        }
    }
    /*
    board[0][0]=board[2][2]=board[2][0]=board[0][2]='O';
    board[1][1]='O';
     */
    
    /*
     //5x5
    board[1][0]=board[2][0]=board[3][0]=board[4][0]='O';
    board[2][1]=board[3][1]='O';
    board[2][2]='O';
    board[3][3]='O';
    board[4][4]='O';
    */
    
    board[0][1]=board[0][3]=board[0][5]='O';
    board[1][0]=board[1][2]=board[1][4]='O';
    board[2][1]=board[2][3]=board[2][5]='O';
    board[3][0]=board[3][2]=board[3][4]='O';

    
    Solution mysolution;
    mysolution.solve(board);
    
    return 0;
}
