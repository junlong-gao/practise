/*
 * > leetcode submit 668.cpp
 *   ✔ Accepted
 *     69/69 cases passed (58 ms)
 *     Your runtime beats 4.64 % of cpp submissions
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
 * value: 1, 2, 2, 3, 4, 5, 6, 7
 * count: 1, 3, 3, 4, 5, 5, 6, 6
 * rank : 1, 2, 3, 4, 5, X, 6, X
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
 * Recall how stl lower_bound, upper_bound works:
 * lower_bound: given a sorted range s and a binary comparator c, return the first
 * element e so that c(e, target) is false.
 * upper_bound: given a sorted range s and a binary comparator c, return the first
 * element e so that c(target, e) is true.
 * Example:
 *  std::vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20

    std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

    std::vector<int>::iterator low,up;
    low=std::lower_bound (v.begin(), v.end(), 20); //          ^
    up= std::upper_bound (v.begin(), v.end(), 20); //                   ^

    Thus for this problem we use the lower_bound.

    Key idea:
    1) How to define the comparator? Comparator should behave as if
       it is
       a) index into the range,
       b) return the comparison result.
    2) How to implement your own lower_bound and upper_bound?
 */

using ull = unsigned long long;
int n, m, k;

bool count(ull x) {
   int t = 0;
   for (int i = 1; i <= m; i++) {
      t += std::min((ull)(x / i), (ull)n);
   }
   return t < k;
}

struct nit {
   bool operator<(const nit& rhs) const {
      //cout << (ull)this << endl;
      return count((ull)this);
   }
};

class Solution {
public:
    int findKthNumber(int mm, int nn, int kk) {
       m = mm, n = nn, k = kk;
       ull ret = (ull)lower_bound((nit*)1, (nit*)(m * n + 1), nit());

       return ret;
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
