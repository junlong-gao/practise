/*
 * > lcg 798
*    Accepted
*    36/36 cases passed (40 ms)
*    Your runtime beats 49.76 % of cpp submissions
*
 * [814] Smallest Rotation with Highest Score
 *
 * https://leetcode.com/problems/smallest-rotation-with-highest-score/description/
 *
 * algorithms
 * Hard (26.81%)
 * Total Accepted:    745
 * Total Submissions: 3K
 * Testcase Example:  '[2,3,1,4,0]'
 *
 *  Given an array A, we may rotate it by a non-negative integer K so that the
 * array becomes A[K], A[K+1], A{K+2], ... A[A.length - 1], A[0], A[1], ...,
 * A[K-1].  Afterward, any entries that are less than or equal to their index
 * are worth 1 point. 
 *
 * For example, if we have [2, 4, 1, 3, 0], and we rotate by K = 2, it becomes
 * [1, 3, 0, 2, 4].  This is worth 3 points because 1 > 0 [no points], 3 > 1
 * [no points], 0 <= 2 [one point], 2 <= 3 [one point], 4 <= 4 [one point].
 *
 * Over all possible rotations, return the rotation index K that corresponds to
 * the highest score we could receive.  If there are multiple answers, return
 * the smallest such index K.
 *
 *
 * Example 1:
 * Input: [2, 3, 1, 4, 0]
 * Output: 3
 * Explanation:
 * Scores for each K are listed below:
 * K = 0,  A = [2,3,1,4,0],    score 2
 * K = 1,  A = [3,1,4,0,2],    score 3
 * K = 2,  A = [1,4,0,2,3],    score 3
 * K = 3,  A = [4,0,2,3,1],    score 4
 * K = 4,  A = [0,2,3,1,4],    score 3
 *
 *
 * So we should choose K = 3, which has the highest score.
 *
 *
 *
 *
 * Example 2:
 * Input: [1, 3, 0, 2, 4]
 * Output: 0
 * Explanation:  A will always have 3 points no matter how it shifts.
 * So we will choose the smallest K, which is 0.
 *
 *
 * Note:
 *
 *
 * A will have length at most 20000.
 * A[i] will be in the range [0, A.length].
 *
 *
 * Digestion:
 * Consider example:
 *         0 1 2 3 4
 *
 * k = 0   2 3 1 4 0
 * k = 1   3 1 4 0 2
 * k = 2   1 4 0 2 3
 * k = 3   4 0 2 3 1
 * k = 4   0 2 3 1 4
 * k = 5   2 3 1 4 0
 *
 * The trick is to assign each element with the contribution after kth shift:
 *
 *         2 3 1 4 0
 * k = 0   0 0 1 0 1   2
 * k = 1   1 0 1 0 1   3
 * k = 2   1 1 0 0 1   3
 * k = 3   1 1 1 0 1   4
 * k = 4   0 0 1 1 1   3
 * k = 5   0 0 1 0 1   2
 *
 * Looking at the contribution table we see that there is already some
 * interesting patterns:
 * 1. 0 and N does not changes the contribution: 0 will always get point,
 *    N will never get point.
 * 2. The change of contribution per value has some nice pattern: it jumps
 *    from 0 to 1 then backs to 0, or from 1 to 0 then to 1.
 * 3. The maximal value of total score can be determined by looking at
 *    accumulative changes.
 *
 * Let's analysis 2 at bit more:
 *
 *          2  3  1  4  0
 * k = 0   +1  0  0  0  0    +1
 * k = 1    0 +1 -1  0  0     0
 * k = 2    0  0 +1  0  0    +1
 * k = 3   -1 -1  0 +1  0    -1
 * k = 4    0  0  0 -1  0    -1
 * k = 5
 *
 * The diff table shows the change of each element's contribution
 * For example, row k says the contribution change from k shift to k+1 shift
 * Observation:
 * 1) For value other than 0 or N, its contribution change to +1 exactly once,
 *    and at its index (for example, element 2 at index 0 will immediately
 *    switch to contribution 1 from 0 shift to 1 shift, element 3 at index 1
 *    will immediately switch to contribution 1 from shift 1 to shift 2).
 * 2) For each value other than 0 or N, its contribution change to -1 exactly
 *    once, when shifted to the index equal to its value. For example, say
 *    the first element shift by x to have index 2, because after x shift,
 *    its index become (i - x) % N, so (i - x) % N = A[x] gives
 *    x = (i - A[i]) % N
 *    for i = 0, A[i] = 2, x = 3, where k = 3, its contribution is -1, this
 *    is because after this shift, its index will fall less than its value.
 *
 * Therefore, all we need to to is to construct the above diff table and
 * use the diff table to find the score (relative to the original score)
 * and output the first max.
 */
class Solution {
public:
    int bestRotation(vector<int>& A) {
       int N = A.size();
       vector<int> diff(N, 0); // each is a row in the above diff table.
       for (int i = 0; i < N; ++i) {
          if (A[i] == 0 || A[i] >= N) continue;
          diff[i] = 1;
       }

       for (int i = 0; i < N; ++i) {
          if (A[i] == 0 || A[i] >= N) continue;
          diff[((i - A[i]) + N) % N] --;
       }

       int best = 0, k = 0;
       for (int i = 0; i < N; ++i) {
          diff[i] = diff[i] + ((i == 0) ? 0 : diff[i - 1]);
          if (diff[i] > best) {
             best = diff[i];
             // diff table's ith row is the change from i shift to i + 1
             // shift, which is the effect of the i + 1 th rotation.
             k = i + 1;
          }
       }

       return k;
    }
};


/*
TESTS
[5, 1, 2, 3, 0]
[1, 3, 0, 2, 4]
[2, 3, 1, 4, 0]
*/
