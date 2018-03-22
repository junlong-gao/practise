/*
 * > leetcode submit 786.cpp
 *   ✔ Accepted
 *   ✔ 62/62 cases passed (66 ms)
 *   ✔ Your runtime beats 75.34 % of cpp submissions
 *
 * [802] K-th Smallest Prime Fraction
 *
 * https://leetcode.com/problems/k-th-smallest-prime-fraction/description/
 *
 * algorithms
 * Hard (27.71%)
 * Total Accepted:    1.6K
 * Total Submissions: 5.4K
 * Testcase Example:  '[1,2,3,5]\n3'
 *
 * A sorted list A contains 1, plus some number of primes.  Then, for every p <
 * q in the list, we consider the fraction p/q.
 *
 * What is the K-th smallest fraction considered?  Return your answer as an
 * array of ints, where answer[0] = p and answer[1] = q.
 *
 *
 * Examples:
 * Input: A = [1, 2, 3, 5], K = 3
 * Output: [2, 5]
 * Explanation:
 * The fractions to be considered in sorted order are:
 * 1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
 * The third fraction is 2/5.
 *
 * Input: A = [1, 7], K = 1
 * Output: [1, 7]
 *
 *
 * Note:
 *
 *
 * A will have length between 2 and 2000.
 * Each A[i] will be between 1 and 30000.
 * K will be between 1 and A.length * (A.length - 1) / 2.
 *
 */
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
       double lo = (double)1 / ((double)A.back() + (double)1), hi = 1;
       double eps = 0.000000001;
       double up, down;
       while (hi - lo > eps) {
          double mid = lo + (hi - lo) / 2;

          // find the best fraction < mid, it is unique
          double best = 1;
          for (int i = 1; i < A.size(); ++i) {
             double q = A[i];
             auto it = std::upper_bound(A.begin(), A.begin() + i, mid * q);
             double p = (it == A.begin()) ? *it : *(it - 1);
             if (mid < p / q) continue;
             if (best > mid - p / q) {
               best =  mid - p / q;
               up = p; down = q;
             }
          }

          // count its rank
          int count = 0;
          for (int i = 1; i < A.size(); ++i) {
             auto it = std::upper_bound(A.begin(), A.begin() + i, 0,
                   [&](const double &dummy, const double &v){ return up * A[i] < v * down; });
             count += (it - A.begin());
          }

          if (count > K) {
             hi = mid;
          } else if (count < K) {
             lo = mid;
          } else {
             return {(int)up, (int)down};
          }
       }

       return {(int)up, (int)down};
    }
};


/*
 *
*/
/*
TESTS
[1,2,3,5]
1
[1,2,3,5]
2
[1,2,3,5]
3
[1,2,3,5]
4
[1,2,3,5]
5
[1,2,3,5]
6
[1,2,3,5,7,11]
1
[1,2,3,5,7,11]
2
[1,2,3,5,7,11]
3
[1,2,3,5,7,11]
4
[1,2,3,5,7,11]
5
[1,2,3,5,7,11]
6
[1,2,3,5,7,11]
7
[1,2,3,5,7,11]
8
[1,2,3,5,7,11]
9
[1,2,3,5,7,11]
10
[1,2,3,5,7,11]
11
[1,2,3,5,7,11]
12
[1,2,3,5,7,11]
13
[1,2,3,5,7,11]
14
[1,2,3,5,7,11]
15
[1,2029,3209,3517,3823,4933,8209,8893,12763,12799,14197,14387,18973,19207,23747,24547,24953,25247,25763,27043]
1
[1,2029,3209,3517,3823,4933,8209,8893,12763,12799,14197,14387,18973,19207,23747,24547,24953,25247,25763,27043]
171
[1,2029,3209,3517,3823,4933,8209,8893,12763,12799,14197,14387,18973,19207,23747,24547,24953,25247,25763,27043]
170
*/
