/*
 * leetcode submit 773.cpp
 *   ✔ Accepted
 *   ✔ 32/32 cases passed (6 ms)
 *   ✔ Your runtime beats 82.95 % of cpp submissions
 *
 * [787] Sliding Puzzle
 *
 * https://leetcode.com/problems/sliding-puzzle/description/
 *
 * algorithms
 * Hard (47.15%)
 * Total Accepted:    2.4K
 * Total Submissions: 5K
 * Testcase Example:  '[[1,2,3],[4,0,5]]'
 *
 * On a 2x3 board, there are 5 tiles represented by the integers 1 through 5,
 * and an empty square represented by 0.
 * 
 * A move consists of choosing 0 and a 4-directionally adjacent number and
 * swapping it.
 * 
 * The state of the board is solved if and only if the board is
 * [[1,2,3],[4,5,0]].
 * 
 * Given a puzzle board, return the least number of moves required so that the
 * state of the board is solved. If it is impossible for the state of the board
 * to be solved, return -1.
 * 
 * Examples:
 * 
 * 
 * Input: board = [[1,2,3],[4,0,5]]
 * Output: 1
 * Explanation: Swap the 0 and the 5 in one move.
 * 
 * 
 * 
 * Input: board = [[1,2,3],[5,4,0]]
 * Output: -1
 * Explanation: No number of moves will make the board solved.
 * 
 * 
 * 
 * Input: board = [[4,1,2],[5,0,3]]
 * Output: 5
 * Explanation: 5 is the smallest number of moves that solves the board.
 * An example path:
 * After move 0: [[4,1,2],[5,0,3]]
 * After move 1: [[4,1,2],[0,5,3]]
 * After move 2: [[0,1,2],[4,5,3]]
 * After move 3: [[1,0,2],[4,5,3]]
 * After move 4: [[1,2,0],[4,5,3]]
 * After move 5: [[1,2,3],[4,5,0]]
 * 
 * 
 * 
 * Input: board = [[3,2,4],[1,5,0]]
 * Output: 14
 * 
 * 
 * Note:
 * 
 * 
 * board will be a 2 x 3 array as described above.
 * board[i][j] will be a permutation of [0, 1, 2, 3, 4, 5].
 * 
 * [0 1 2
 *  3 4 5]
 */
class Solution {
   const string target = "123450";
   const vector<vector<int>> next = {
      {-1, -1, 1, 3},
      {0, -1, 2, 4},
      {1, -1, -1, 5},
      {-1, 0, 4, -1},
      {3, 1, 5, -1},
      {4, 2, -1, -1}
   };
public:
    int slidingPuzzle(vector<vector<int>>& board) {
       unordered_map<string, int> g;
       string init;
       int zero = 0;
       for (int i = 0; i < 2; ++i) { for (int j = 0; j < 3; ++j) {
          init += board[i][j] + '0';
          if (board[i][j] == 0) {
             zero = i * 3 + j;
          }
       }}

       deque<pair<string, int>> q;
       q.push_back(make_pair(init, zero));
       g[init] = 0;
       while (!q.empty()) {
          auto top = q.front();
          int dist = g[top.first];
          q.pop_front();

          if (top.first == target) return dist;

          for (int i = 0; i < 4; ++i) {
             int idx = next[top.second][i];
             if (idx < 0) continue;
             string node = top.first;
             swap(node[top.second], node[idx]);
             if (g.count(node) == 0) {
                g[node] = dist + 1;
                q.push_back(make_pair(node, idx));
             }
          }
       }

       return -1;
    }
};


/*
TESTS
[[1,2,3],[4,0,5]]
[[3,2,4],[1,5,0]]
[[1,2,3],[5,4,0]]
*/
