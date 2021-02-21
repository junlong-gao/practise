#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
        if (board.empty()) {
          return 0;
        }
        
        const int n = board.size();
        assert (n == board[0].size());
        // row and col property: each row is either the same as the first row
        // or completely inverted. same for col
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            if (board[0][0] ^ board[i][0] != board[0][j] ^ board[i][j]) {
              return -1;
            }
            if (board[0][0] ^ board[0][j] != board[i][0] ^ board[i][j]) {
              return -1;
            }
          }
        }
        
        // 1, 0 count
        // find swaps: each misplaced will swap with another
        // misplaced.
        int colSwap = 0, rowSwap = 0, colCount = 0, rowCount = 0;
        for (int i = 0; i < n; ++i) {
          if (board[0][i] == 1) colCount++;
          if (board[i][0] == 1) rowCount++;
          if (board[0][i] % 2 != i % 2) colSwap++;
          if (board[i][0] % 2 != i % 2) rowSwap++;
        }
        
        if ((std::abs(n - 2 * colCount) > 1) || (std::abs(n - 2 * rowCount) > 1)) return -1;
        if (n % 2 == 0) {
          /*
          even case
          rowSwap / 2 == k:
             0       1
          v1 k      n - k
          v2 n- k     k
          
          colSwap / 2 == j:
             0       1
          v1 j      n - j
          v2 n- j     j
          
          0 means start with 0, 1 means start with 1.
          v1 means same as row/col 0, v2 means exactly opposite of row/col 0
          the matrix gives the possible values.
          The calculation only consider starting with 0, because the rest of the 3
          are related.
          The key observation is, if you swap col, the only way you affect row
          swapping is to swap a v2 col with the first col. But then when you swap row,
          both variants (start with 0 or 1) will also ask you to pick between j and n-j.
          For example, if your col swapping does not touch the frist col, when
          you do row swapping, you are to pick between j and n - j (calculated j, and
          check n -j < j). If your col swapping does swap on first col, when you do
          row swapping, you are to pick between n -j and j. So either way, 
          for calculated k you are to pick between j and n -j.
          
          Of course you have two ks to consider (k and n -k), and if you settle with n -k,
          the above arguments still allow you to pick both j and n - j.
          */
          int colMin = std::min(colSwap, n - colSwap);
          int rowMin = std::min(rowSwap, n - rowSwap);
          assert((colMin % 2 == 0) && (rowMin % 2 == 0));
          return colMin / 2 + rowMin / 2;
        } else {
          /*
          For odd case, the above opt strategy will yield two possible values:
          n / 2 and n / 2 + 1
          One of them will be even.
          For odd cases, the chessboard is unique. So there is only one way for the 
          first row to end up with (start with 0 or 1).
          Because the caculation is based on 0 start, if the solution should be 2 start, 
          the value are all off by 1, resulting value (odd) = n (odd) - true value (even). 
          So if we find resulting value is odd, we flip it by n to obtain true value.
          
          We do not have the choices as in even case as there is only one way to have the 
          first row or col.
          */
          if (colSwap % 2) colSwap = n - colSwap;
          if (rowSwap % 2) rowSwap = n - rowSwap;
          return colSwap / 2 + rowSwap / 2;
        }
        return 0;
    }
};
int main() {
  vector<pair<vector<vector<int>>, int>> ts {
    {{ {0, 1}, {0, 1} },
    -1},
    {{ {0, 1}, {1, 0} },
    0},
    {{ {1, 1}, {1, 0} },
    -1},
    {{ {1, 1}, {1, 1} },
    -1},
    {{ {1, 1, 0}, {0, 0, 1}, {0, 0, 1}},
    2},
    {{ {0, 1, 1}, {1, 0, 0}, {1, 0, 0}},
    2},
    {{ {0, 1, 1, 0}, {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 1, 0}},
    2},
  };
  
  for (auto t: ts) {
    Solution s;
    auto v = s.movesToChessboard(t.first);
    cout << v << " " << t.second << endl;;
    assert(v == t.second);
  }
  
  cout << "... PASS" << endl;
  
}
