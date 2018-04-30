/*
 * [631] Design Excel Sum Formula
 *
 * https://leetcode.com/problems/design-excel-sum-formula/description/
 *
 * algorithms
 * Hard (27.95%)
 * Total Accepted:    1.9K
 * Total Submissions: 7K
 * Testcase Example:  '["Excel","get","set","get"]\n[[3,"C"],[1,"A"],[1,"A",1],[1,"A"]]'
 *
 * Your task is to design the basic function of Excel and implement the
 * function of sum formula.  Specifically, you need to implement the following
 * functions:
 *
 *
 *
 * Excel(int H, char W): This is the constructor. The inputs represents the
 * height and width of the Excel form. H is a positive integer, range from 1 to
 * 26. It represents the height. W is a character range from 'A' to 'Z'. It
 * represents that the width is the number of characters from 'A' to W. The
 * Excel form content is represented by a height * width 2D integer array C, it
 * should be initialized to zero. You should assume that the first row of C
 * starts from 1, and the first column of C starts from 'A'.
 *
 *
 *
 * void Set(int row, char column, int val): Change the value at C(row, column)
 * to be val.
 *
 * int Get(int row, char column): Return the value at C(row, column).
 *
 * int Sum(int row, char column, List of Strings : numbers): This function
 * calculate and set the value at C(row, column), where the value should be the
 * sum of cells represented by numbers. This function return the sum result at
 * C(row, column). This sum formula should exist until this cell is overlapped
 * by another value or another sum formula.
 *
 * numbers is a list of strings that each string represent a cell or a range of
 * cells. If the string represent a single cell, then it has the following
 * format : ColRow. For example, "F7" represents the cell at (7, F).
 *
 * If the string represent a range of cells, then it has the following format :
 * ColRow1:ColRow2. The range will always be a rectangle, and ColRow1 represent
 * the position of the top-left cell, and ColRow2 represents the position of
 * the bottom-right cell.
 *
 * Example 1:
 *
 * Excel(3,"C");
 * // construct a 3*3 2D array with all zero.
 * //   A B C
 * // 1 0 0 0
 * // 2 0 0 0
 * // 3 0 0 0
 *
 * Set(1, "A", 2);
 * // set C(1,"A") to be 2.
 * //   A B C
 * // 1 2 0 0
 * // 2 0 0 0
 * // 3 0 0 0
 *
 * Sum(3, "C", ["A1", "A1:B2"]);
 * // set C(3,"C") to be the sum of value at C(1,"A") and the values sum of the
 * rectangle range whose top-left cell is C(1,"A") and bottom-right cell is
 * C(2,"B"). Return 4.
 * //   A B C
 * // 1 2 0 0
 * // 2 0 0 0
 * // 3 0 0 4
 *
 * Set(2, "B", 2);
 * // set C(2,"B") to be 2. Note C(3, "C") should also be changed.
 * //   A B C
 * // 1 2 0 0
 * // 2 0 2 0
 * // 3 0 0 6
 *
 *
 *
 * Note:
 *
 * You could assume that there won't be any circular sum reference. For
 * example, A1 = sum(B1) and B1 = sum(A1).
 * ⁠The test cases are using double-quotes to represent a character.
 * Please remember to RESET your class variables declared in class Excel, as
 * static/class variables are persisted across multiple test cases. Please see
 * here for more details.
 *
 *
 */
class Excel {
   unordered_map<int, unordered_map<int, vector<pair<int, int>>>> dependency;
   unordered_map<int, unordered_map<int, vector<pair<int, int>>>> children;
   vector<vector<int>> g;

   int to_int(char c) {
      return c - 'A';
   }

public:
    Excel(int H, char W) {
       g = vector<vector<int>>(H + 1, vector<int>(W, 0));
    }

    void set(int r, char cc, int v) {
       struct point {
          int row, col;
       };
       int c = to_int(cc);
       for (auto &child : children[r][c]) {
          auto it = find(dependency[child.first][child.second].begin(),
                         dependency[child.first][child.second].end(),
                         pair<int, int>(r, c));
          dependency[child.first][child.second].erase(it);
       }

       children[r][c].clear();

       int delta = v - g[r][c];
       deque<point> q;
       q.push_back({r, c});
       while(!q.empty()) {
          auto top = q.front();
          q.pop_front();
          g[top.row][top.col] += delta;
          //cout << "top update: " << top.row << " " << top.col << " " << g[top.row][top.col] << endl;
          for (const auto & p : dependency[top.row][top.col]) {
             q.push_back({p.first, p.second});
          }
       }
    }

    int get(int r, char c) {
       //cout << "get: " << r << " " << to_int(c) << " " << g[r][to_int(c)] << endl;
       return g[r][to_int(c)];
    }

    int sum(int rr, char cc, vector<string> strs) {
       int ret = 0;
       int c = to_int(cc);
       int r = rr;

       // remove old
       for (auto &child : children[r][c]) {
          auto it = find(dependency[child.first][child.second].begin(),
                         dependency[child.first][child.second].end(),
                         pair<int, int>(r, c));
          dependency[child.first][child.second].erase(it);
       }

       children[r][c].clear();

       for (const string &reg: strs) {
          auto pos = reg.find(":");
          vector<string> to_parse;
          if (pos != std::string::npos) {
             auto begin = reg.substr(0, pos);
             auto end = reg.substr(pos + 1);
             int colBegin = to_int(begin[0]);
             int colEnd = to_int(end[0]);
             int rowBegin = stoi(begin.substr(1));
             int rowEnd = stoi(end.substr(1));
             for (int x = rowBegin; x <= rowEnd; ++x) {
                for (int y = colBegin; y <= colEnd; ++y) {
                   dependency[x][y].push_back({r, c});
                   children[rr][c].push_back({x, y});
                   ret += g[x][y];
                }
             }
          } else {
             int col = to_int(reg[0]);
             int row = stoi(reg.substr(1));
             dependency[row][col].push_back({r, c});
             children[r][c].push_back({row, col});
             ret += g[row][col];
          }
       }

       g[r][c] = ret;
       return ret;
    }
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel obj = new Excel(H, W);
 * obj.set(r,c,v);
 * int param_2 = obj.get(r,c);
 * int param_3 = obj.sum(r,c,strs);
 */


/*
TESTS
["Excel","sum","set","get", "sum", "set", "get", "get"]
[[26,"Z"],[3, "C", ["A1:B2"]],[1,"A",1],[3,"C"],[4,"C",["C3"]],[2, "A", 2], [3, "C"], [4,"C"]]
["Excel","set","get"]
[[26,"Z"],[1,"A",2], [1, "A"]]
["Excel","set","get", "sum"]
[[26,"Z"],[1,"A",2], [1, "A"], [3, "C", ["A1:B2"]]]
["Excel","set","sum","set","get","set","get"]
[[5,"E"],[1,"A",1],[2,"B",["A1"]],[2,"B",0],[2,"B"],[1,"A",5],[2,"B"]]
*/
