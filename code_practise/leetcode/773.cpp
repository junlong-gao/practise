/*
 * > lc submit 773.cpp
    ✔ Accepted
    ✔ 32/32 cases passed (10 ms)
 */
/*
 * [787] Sliding Puzzle
 *
 * https://leetcode.com/problems/sliding-puzzle/description/
 *
 * algorithms
 * Hard (47.08%)
 * Total Accepted:    2.2K
 * Total Submissions: 4.6K
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
 */
class Solution {
   int dx[4] = {0, 1, 0, -1};
   int dy[4] = {1, 0, -1, 0};

   unordered_set<string> visited;

   const string t = "123450";

   const vector<vector<int>> stable {
      {-1, -1, 1, 3},
      {0, -1, 2, 4},
      {1, -1, -1, 5},
      {-1, 0, 4, -1},
      {3, 1, 5, -1},
      {4, 2, -1, -1}
   };

   struct state {
      int zero;
      int d;
      string b;
   };
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        deque<state> q;
        string cur = [&] {
            string next;
            for (int k = 0; k < 3; ++k) {
               next += board[0][k] + '0';
            }

            for (int k = 0; k < 3; ++k) {
               next += board[1][k] + '0';
            }
            return next;
        } ();
        int z = 0;
        for (int i = 0; i < 6; ++i) {
           if (cur[i] == '0') {
              z = i;
              break;
           }
        }
        q.push_back({z, 0, cur});
        visited.insert(cur);
        while (!q.empty()) {
           auto top = q.front();
           q.pop_front();
           if (top.b == t) {
              return top.d;
           }

           for (int i = 0; i < 4; ++i) {
              int next = stable[top.zero][i];
              if (next < 0) continue;

              string nb = top.b;
              std::swap(nb[top.zero], nb[next]);

              if (visited.count(nb) > 0) continue;

              q.push_back({next, top.d + 1, nb});
              visited.insert(nb);
           }
        }

        return -1;
    }
};


/*
TESTS
[[1,2,3],[4,5,0]]
[[1,2,3],[4,0,5]]
[[1,2,3],[5,4,0]]
[[4,1,2],[5,0,3]]
*/
