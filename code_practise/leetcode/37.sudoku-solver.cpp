/*
 * > leetcode show 37 -g
 * > vi 37.sudoku-solver.cpp
 * > vi 37.sudoku-solver.test
 * > leetcode test 37.sudoku-solver.cpp -t "$(cat 37.sudoku-solver.test)"
 * > leetcode submit 37.sudoku-solver.cpp
 */

class Solution {
   using mask = bitset<10>;
   array<mask, 9> rows, cols, boxes;
   bool test(int i, int j, int v) {
      if (rows[i][v]) return false;
      if (cols[j][v]) return false;
      if (boxes[(i / 3) * 3 + (j / 3) % 3][v]) return false;
      return true;
   }
   void set(int i, int j, int v) {
      rows[i].set(v);
      cols[j].set(v);
      boxes[(i / 3) * 3 + (j / 3) % 3].set(v);
   }
   void unset(int i, int j, int v) {
      rows[i].reset(v);
      cols[j].reset(v);
      boxes[(i / 3) * 3 + (j / 3) % 3].reset(v);
   }
public:
   bool helper(vector<vector<char>>& board, const int x, const int y) {
      for (int i = x; i < 9; ++ i) {
         for (int j = (i == x? y : 0); j < 9; ++j) {
            if (board[i][j] == '.') {
               for (int v = 1; v <= 9; ++v) {
                 if (test(i, j, v)) {
                    set(i, j, v);
                    board[i][j] = v + '0';
                    if (helper(board, i, j)) {
                       return true;
                    }
                    unset(i, j, v);
                    board[i][j] = '.';
                 }
              }
              return false;
            }
         }
      }
      return true;
   }
    void solveSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; ++i) {
           for (int j = 0; j < 9; ++j) {
              if (board[i][j] != '.') {
                 int v = board[i][j] - '0';
                 set(i, j, v);
                  //cout << i << " " << j << " " << v << endl;
              }
           }
        }

        helper(board, 0, 0);
    }
};
