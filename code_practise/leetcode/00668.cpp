/*
   > lcg 668
  ✔ Accepted
  ✔ 69/69 cases passed (30 ms)
    Your runtime beats 15.71 % of cpp submissions
 *
 * [668] Kth Smallest Number in Multiplication Table
 *
 * https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/description/
 *
 * algorithms
 * Hard (39.66%)
 * Total Accepted:    5.2K
 * Total Submissions: 13.2K
 * Testcase Example:  '3\n3\n5'
 *
 *
 * Nearly every one have used the Multiplication Table. But could you find out
 * the k-th smallest number quickly from the multiplication table?
 *
 *
 *
 * Given the height m and the length n of a m * n Multiplication Table, and a
 * positive integer k, you need to return the k-th smallest number in this
 * table.
 *
 *
 * Example 1:
 *
 * Input: m = 3, n = 3, k = 5
 * Output:
 * Explanation:
 * The Multiplication Table:
 * 1    2    3
 * 2    4    6
 * 3    6    9
 *
 * The 5-th smallest number is 3 (1, 2, 2, 3, 3).
 *
 *
 *
 *
 * Example 2:
 *
 * Input: m = 2, n = 3, k = 6
 * Output:
 * Explanation:
 * The Multiplication Table:
 * 1    2    3
 * 2    4    6
 *
 * The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).
 *
 *
 *
 *
 * Note:
 *
 * The m and n will be in the range [1, 30000].
 * The k will be in the range [1, m * n]
 *
 *
 * Digestion:
 * Binary Search
 * Consider this example:
 * Input: m = 2, n = 3, k = 6
 * Output:
 * Explanation:
 * The Multiplication Table:
 * 1    2    3
 * 2    4    6
 *
 * The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).
 * n * m + 1 = 7:
 *
 * k = 5
 * value:    1, 2, 2, 3, 4, 5, 6, 7
 * count:    1, 3, 3, 4, 5, 5, 6, 6
 * cnt >= k: f, f, f, f, t, t, t, t
 * rank :    1, 2, 3, 4, 5, X, 6, X
 *
 * The first column list the search space (not necessarily the values in
 * the table)
 * The second column list the count of values less or equal to the value
 * in the table.
 *
 * So the key observation is:
 * Given rank k, we wish to find the first value in range [1, m*n+1)
 * so that count(val) greater or equal to k.
 *
 * This goes into a deep discussion of binary search of two variants:
 * 1) find the last value to be true
 * 2) find the first value to be true
 *
 * variant       1)                            2)
 * search
 * range:     [lo, hi)                      (lo, hi]

 * final
 * condition:               hi - lo <= 1
 *
 * assume
 * pattern:     t t f f                     f f t t
 *
 * reduce:    if check(mid)               if check(mid)
 *              lo = mid                     hi = mid
 *            else                        else
 *              hi = mid                     lo = mid
 *
 * example
 * check for   check(mid):                check(mid):
 * searching   target >= val[mid]         val[mid] >= target
 * value
 *
 * The only material difference is to find the first or the last,
 * in this problem it requires variant 2)
 */


class Solution {
   int n, m, k;

   bool count(int x) {
      int t = 0;
      for (int i = 1; i <= m; i++) {
         t += std::min(x / i, n);
      }

      return t >= k;
   }

public:
    int findKthNumber(int mm, int nn, int kk) {
       m = mm, n = nn, k = kk;
       if (n < m) {
          std::swap(n, m);
       }

       int lo = 0, hi = n * m; // (lo, hi]
       while (hi - lo > 1) {
          int mid = lo + (hi - lo) / 2;
          if (count(mid)) {
             hi = mid;
          } else {
             lo = mid;
          }
       }

       return hi;
    }
};


/*
TESTS
2
3
6
3
3
5
*/
