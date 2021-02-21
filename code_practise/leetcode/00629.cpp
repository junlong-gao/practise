/*
   > leetcode submit 629.cpp
     ✔ Accepted
     ✔ 80/80 cases passed (33 ms)
     ✔ Your runtime beats 25.33 % of cpp submissions
 *
 * [629] K Inverse Pairs Array
 *
 * https://leetcode.com/problems/k-inverse-pairs-array/description/
 *
 * algorithms
 * Hard (26.88%)
 * Total Accepted:    4.7K
 * Total Submissions: 17.3K
 * Testcase Example:  '3\n0'
 *
 *
 * Given two integers n and k, find how many different arrays consist of
 * numbers from 1 to n such that there are exactly k inverse pairs.
 *
 *
 * We define an inverse pair as following:
 * For ith and jth element in the array, if i < j and a[i] > a[j] then it's an
 * inverse pair; Otherwise, it's not.
 *
 *
 *
 * Since the answer may be very large, the answer should be modulo 109 + 7.
 *
 *
 * Example 1:
 *
 * Input: n = 3, k = 0
 * Output: 1
 * Explanation:
 * Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0
 * inverse pair.
 *
 *
 *
 * Example 2:
 *
 * Input: n = 3, k = 1
 * Output: 2
 * Explanation:
 * The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
 *
 *
 *
 * Note:
 *
 * The integer n is in the range [1, 1000] and k is in the range [0, 1000].
 *
 * Digestion:
 * How many permutations?
 * dp[n][k] = number of permutations of [1, n] having k inverse pairs.
 *          = case n is in the last having k inverse pairs +
 *            case n is not in the last having k inverse pairs
 *
 * when n in the last, all cases form the permutations dp[n-1][k]
 * when n is not in the last, it will form inverse pairs with values after it.
 *      when n is at index 0, then it contributes n - 1 inverse pair, and removing it
 *      gives k - (n - 1) inverse pairs.
 * if n is at index j, it contributes n - 1 - j inverse pair j in [0, n - 1]
 * dp[n][k] = sum_{j in [0, n - 1]} dp[n - 1][k - (n - 1 - j)]
 *          = sum_{j in [0, n - 1]} dp[n - 1][k - j]
 *
 * k <= n * (n - 1) / 2
 * dp[0][0] = 1
 * dp[1][0] = 1 dp[1][1] = 0
 * dp[2][0] = 1 dp[2][1] = 1
 * dp[3][0] = 1 dp[3][1] = 2 dp[3][2] = |{2, 3, 1}, {3, 1, 2}| = 2 dp[3][3] = |{3,2,1}| = 1
 * @@@ dp[3][1] = dp[2][0] + dp[2][1] = 2
 * @@@ dp[3][2] = dp[2][2 - (2 - 0)] + dp[2][2 - (2 - 1)] = 2
 * @@@ dp[3][2] = dp[2][1] + dp[2][3 - (2 - 1)] + dp[2][3 - (2 - 2)] = 1 + 0 + 0
 * as j increases k - (n - 1 - j) increases (break fast?)
 *
 * j - (i - 1 - l) = 0 l = i - 1 - j
 *
 * This TLEs.
 * Looking at the recursion:
 *
 * dp[n][k] = sum_{j in [0, n - 1]} dp[n - 1][k - (n - 1 - j)]
 *          = sum_{j in [0, n - 1]} dp[n - 1][k - j]
 *   let n be fixed. We find that for small k (k in [0, n - 1]), 
 *                    dp[n][k] = dp[i][k-1] + dp[i-1][k]
 *
 *                   For larger k (k  >= n - 1)
 *                   dp[n][k] = dp[n - 1][k] + dp[n-1][k-1] ... + dp[n - 1][k - (n - 1)]
 *                            = sum_{j in [0, k]} dp[n - 1][j] - sum_{j in [0, k - (n-1) - 1]} dp[n - 1][j]
 *                              this is a fixed moving window sum of size (n - 1)
 *                              which can be inductive proved:
 *                              dp[i][k - 1] + dp[i - 1][k] - dp[i - 1][k - i]
 *                              (intuitively, we add dp[i - 1][k] on to the window dp[i][k -1] and remove dp[i -1][k -1]
 *                               from the window)
 */
class Solution {
    //using ull = unsigned long long;
    const int mod = 1000000007;
public:
    int kInversePairs(int n, int k) {
       auto add = [&](int l, int r) {return (l + r) % mod;};
       auto sub = [&](int l, int r) {return (l - r + mod) % mod;};

       vector<vector<int>> dp(std::max(n, 5) + 1, vector<int>(std::max(k, 5) + 1, 0));

       dp[0][0] = 1;
       dp[1][0] = 1;
       dp[2][0] = 1; dp[2][1] = 1;
       dp[3][0] = 1; dp[3][1] = 2; dp[3][2] = 2; dp[3][3] = 1;

       for (int i = 4; i <= n; ++i) { for (int j = 0; j <= k; ++j) {
          if (j == 0) { dp[i][j] = 1; continue; }
          dp[i][j] = add(dp[i][j-1], dp[i-1][j]);
          if (j >= i) {
             dp[i][j] = sub(dp[i][j], dp[i - 1][j - i]);
          }
       }}

       return dp[n][k];
    }
};

/*
 * 
4
0
4
2
4
3
4
4
6
0
6
1
6
2
1000
0
1000
1
1000
1000 // 663677020 
 * */

/*
TESTS
1
0
2
0
3
0
10
20
50
50
100
100
1000
1000
*/
