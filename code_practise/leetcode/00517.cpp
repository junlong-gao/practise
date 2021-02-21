/*
 * [517] Super Washing Machines
 *
 * https://leetcode.com/problems/super-washing-machines/description/
 *
 * algorithms
 * Hard (36.16%)
 * Total Accepted:    8.2K
 * Total Submissions: 22.6K
 * Testcase Example:  '[1,0,5]'
 *
 * You have n super washing machines on a line. Initially, each washing machine
 * has some dresses or is empty.
 *
 *
 * For each move, you could choose any m (1 ≤ m ≤ n) washing machines, and pass
 * one dress of each washing machine to one of its adjacent washing machines
 * at the same time .
 *
 * Given an integer array representing the number of dresses in each washing
 * machine from left to right on the line, you should find the minimum number
 * of moves to make all the washing machines have the same number of dresses.
 * If it is not possible to do it, return -1.
 *
 * Example1
 *
 * Input: [1,0,5]
 *
 * Output: 3
 *
 * Explanation:
 * 1st move:    1     0     1     1     4
 * 2nd move:    1     2     1     3
 * 3rd move:    2     1     2     2     2
 *
 *
 * Example2
 *
 * Input: [0,3,0]
 *
 * Output: 2
 *
 * Explanation:
 * 1st move:    0     1     2     0
 * 2nd move:    1     2 --> 0    =>    1     1     1
 *
 *
 * Example3
 *
 * Input: [0,2,0]
 *
 * Output: -1
 *
 * Explanation:
 * It's impossible to make all the three washing machines have the same number
 * of dresses.
 *
 *
 *
 *
 * Note:
 *
 * The range of n is [1, 10000].
 * The range of dresses number in a super washing machine is [0, 1e5].
 *
 *
 * Digestion:
 * To reduce complexity, we think each machine only gives out cloth, instead
 * of both giving out and receive.
 *
 * Then, any valid move sequence can be though as assigning +1/-1 to each machine
 * per move:
 * Example
 *
 * Input: [1,0,5]
 *
 * one possible move seq:
 * mach:   0   1   2
 * move 1: 0  -1  +1
 * move 2: -1  0  +1
 * move 3: 0  -1  +1
 *
 * another possible move seq:
 * mach:   0   1   2
 * move 1: 0  -1  +1
 * move 2: 0  -1  +1
 * move 3: 0  -1  +1
 * move 4:-1  +1   0
 *
 * another possible move seq:
 * mach:   0   1   2
 * move 1: +1 -2  +1
 * move 2: -1  0  +1
 * move 3: -1  0  +1
 *
 * target: -1  -2  +3
 *
 * Input: [0,1,5]
 * target: -2 -1 +3
 * another possible move seq:
 * mach:   0   1   2
 * move 1: -2 +1  +1
 * move 2: 0  -1  +1
 * move 3: 0  -1  +1
 *
 * The key observation are as follows:
 * - A move is identified by a sequence of alternating +1/-n.
 *   That is, a machine can give at most one cloth but can receive n >= 1 cloths.
 *
 * -. For every mach (every column), the sum represents the amount of cloth to
 *  give as the result of the move seq and must equal to the difference between
 *  its start and finish.  Otherwise it will not end up with the final target
 *  cloth count.
 *  For each machine at most one cloth it can give in a move, thus the lower
 *  bound of move set is the maximal of these columns' giving count.
 *
 * -. For every move (every row),  If we iterate from left to right and sum the
 *  give along the way, the sum indicates the flow at each point from left to
 *  right: the net out from the left part into right part.  Because each round
 *  at any machine can give at most one cloth, the peak indicates the minimal
 *  of moves.
 *
 * let alpha = max(column max, max(flow coming out from left))
 * we conclude the optimal has the lower bound alpha.
 *
 * Once we know the giving out array, constructing a solution that achieves
 * the lower bound is always possible.
 * +1's must occupy a single row, but -n can span a number of rows less than n.
 * for example:
 *                   9  1  8  8  9
 * giving out array: 2 -6  1  1  2
 *                  +1 -1
 *                  +1 -1
 *                     -3 +1 +1 +1
 *                     -1       +1
 * // TODO
 */
class Solution {
public:
    int findMinMoves(vector<int>& machines) {
       int sum = 0;
       int n = machines.size();
       for (auto e : machines) {
          sum += e;
       }

       if (sum % n != 0) return -1;

       int ave = sum / n;
       for (int i = 0; i < n; ++i) {
          machines[i] -= ave;
       }

       int flow = 0;
       int ret = 0;
       for (int i = 0; i < n; ++i) {
          int h = machines[i];
          flow += h;
          ret = std::max(ret, std::max(std::abs(flow), h));
       }
       assert(flow == 0);

       return ret;
    }
};

/*
TESTS
[9,1,8,8,9]
*/
