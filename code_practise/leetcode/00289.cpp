//
// Created by Junlong Gao on 8/6/16.
//

#ifndef PRACTISE_SOLUION_H
#define PRACTISE_SOLUION_H
#include<vector>
using namespace std;
class Soluion {
    int width, height;
    int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    bool valid(int x, int y){
        if(x<0 || x >= width) return false;
        if(y<0 || y >= height) return false;
        return true;
    }
    int getLiveCount(vector<vector<int>>& board, int x, int y){
       int ret = 0;
       for(int i = 0; i < 8; ++i){
           int nx = x +dx[i], ny = y + dy[i];
           if(valid(nx, ny)){
              ret += board[nx][ny] & 1;
           }
       }
       return ret;
    }
    void setPoint(vector<vector<int>>& board, int x, int y){
        int live = getLiveCount(board, x, y);
        int state = board[x][y] & 1;
        if(state == 1){
           if(live >= 2 && live <= 3) {
               board[x][y] = 3;
           }
        }else{
            if(live == 3){
                board[x][y] = 2;
            }
        }
    }
public:
    void gameOfLife(vector<vector<int>>& board) {
        width = board.size();
        if(width < 1) return;
        height = board[0].size();
        for(int x = 0; x < width; ++x){
            for(int y = 0; y < height; ++y){
                setPoint(board, x, y);
            }
        }
        for(int x = 0; x < width; ++x){
            for(int y = 0; y < height; ++y){
                board[x][y] >>= 1;
            }
        }
    }
};


#endif //PRACTISE_SOLUION_H
