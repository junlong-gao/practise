/*
 * > leetcode submit 780.cpp
 *   ✔ Accepted
 *     189/189 cases passed (8 ms)
 *     Your runtime beats 5.7 % of cpp submissions
 */
/*
 * [796] Reaching Points
 *
 * https://leetcode.com/problems/reaching-points/description/
 *
 * algorithms
 * Hard (21.04%)
 * Total Accepted:    2.2K
 * Total Submissions: 10.3K
 * Testcase Example:  '9\n5\n12\n8'
 *
 * A move consists of taking a point (x, y) and transforming it to either (x,
 * x+y) or (x+y, y).
 *
 * Given a starting point (sx, sy) and a target point (tx, ty), return True if
 * and only if a sequence of moves exists to transform the point (sx, sy) to
 * (tx, ty). Otherwise, return False.
 *
 *
 * Examples:
 * Input: sx = 1, sy = 1, tx = 3, ty = 5
 * Output: True
 * Explanation:
 * One series of moves that transforms the starting point to the target is:
 * (1, 1) -> (1, 2)
 * (1, 2) -> (3, 2)
 * (3, 2) -> (3, 5)
 *
 * Input: sx = 1, sy = 1, tx = 2, ty = 2
 * Output: False
 *
 * Input: sx = 1, sy = 1, tx = 1, ty = 1
 * Output: True
 *
 *
 *
 * Note:
 *
 *
 * sx, sy, tx, ty will all be integers in the range [1, 10^9].
 *
 * Digestion:
 * x, y -> x + y, y
 *         x, x + y
 * Not obvious. Think conversely:
 * u, v <- u - v, v
 *         u, v - u
 * This leads to an interesting observation: as all values are > 0,
 * given u, v (u != v), if u > v, it must come from the first transform,
 * otherwise the second. This quickly gives an inductive way of finding previous
 * point. Keep subtracting v from u until u <= v or u <= sx.
 *
 * The reduction stops if the larger of the target is not larger than the
 * corresponding source.
 *
 * This can be made significantly faster as we can compress multiple
 * tx = tx - ty into a single tx = tx - (tx - sx) / ty * ty.
 */
class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        while (tx != ty) {
           if (tx > ty) {
              if (tx <= sx) break;
              tx -= (tx - sx) / ty * ty;
              while (tx > ty && tx > sx) {
                 tx -= ty;
              }
           }
           else {
              if (ty <= sy) break;
              ty -= (ty - sy) / tx * tx;
              while (ty > tx && ty > sy) {
                 ty -= tx;
              }
           }
        }

        return tx == sx && ty == sy;
    }
};

/*
TESTS
9
10
9
19
9
10
9
23
9
5
12
8
1
1
2
2
1
1
1
1
1
1
3
5
1
1
1000000000
1
1
5
19
5
*/
