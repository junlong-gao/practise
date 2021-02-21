/*
> lcg 757
  ✔ Accepted
  ✔ 113/113 cases passed (42 ms)
  ✔ Your runtime beats 72.19 % of cpp submissions
*/

/*
 * [759] Set Intersection Size At Least Two
 *
 * https://leetcode.com/problems/set-intersection-size-at-least-two/description/
 *
 * algorithms
 * Hard (34.79%)
 * Total Accepted:    1.8K
 * Total Submissions: 5.2K
 * Testcase Example:  '[[1,3],[1,4],[2,5],[3,5]]'
 *
 *
 * An integer interval [a, b] (for integers a < b) is a set of all consecutive
 * integers from a to b, including a and b.
 *
 * Find the minimum size of a set S such that for every integer interval A in
 * intervals, the intersection of S with A has size at least 2.
 *
 *
 * Example 1:
 *
 * Input: intervals = [[1, 3], [1, 4], [2, 5], [3, 5]]
 * Output: 3
 * Explanation:
 * Consider the set S = {2, 3, 4}.  For each interval, there are at least 2
 * elements from S in the interval.
 * Also, there isn't a smaller size set that fulfills the above condition.
 * Thus, we output the size of this set, which is 3.
 *
 *
 *
 * Example 2:
 *
 * Input: intervals = [[1, 2], [2, 3], [2, 4], [4, 5]]
 * Output: 5
 * Explanation:
 * An example of a minimum sized set is {1, 2, 3, 4, 5}.
 *
 *
 *
 * Note:
 * intervals will have length in range [1, 3000].
 * intervals[i] will have length 2, representing some integer interval.
 * intervals[i][j] will be an integer in [0, 10^8].
 *
 */
class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
       sort(intervals.begin(), intervals.end(),
          [&](vector<int> & l, vector<int> & r) {
          // consider:
          // x   y
          //   [             ]
          //      [          ]
          //         [       ]
          //            [    ]
          //              [  ]
          //
          if (l[1] != r[1]) {
             return l[1] < r[1];
          }

          return l[0] > r[0];
       });

       pair<int, int> last_two {-1, -1};
       int counter = 0;
       for (auto ii : intervals) {
          //cout << ii[0] << ", " << ii[1] << endl;
          if (last_two == pair<int,int>{-1, -1}) {
             last_two = {ii[1] - 1, ii[1]};
             counter += 2;
             //cout << "+2" << endl;
             continue;
          }

          // efficiently know whether interset or not:
          if (last_two.first >= ii[0]) {
             // opt cannot do better than us at this point.
             continue;
          }

          if (last_two.first < ii[0] &&
              ii[0] <= last_two.second) {
            last_two.first = last_two.second;
            last_two.second = ii[1];
            counter += 1;
            //cout << "+1" << endl;
            continue;
          }

          last_two.first = ii[1] - 1;
          last_two.second = ii[1];
          counter += 2;
          //cout << "+2" << endl;
       }

       return counter;
    }
};

/*
 *
*/

/*
TESTS
[[1,3],[1,4],[2,5],[3,5]]
[[1, 2], [2, 3], [2, 4], [4, 5]]
[[2,10],[3,7],[3,15],[4,11],[6,12],[6,16],[7,8],[7,11],[7,15],[11,12]]
*/
