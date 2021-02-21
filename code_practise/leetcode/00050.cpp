/*
 * [50] Pow(x, n)
 *
 * https://leetcode.com/problems/powx-n/description/
 *
 * algorithms
 * Medium (26.11%)
 * Total Accepted:    212K
 * Total Submissions: 812.1K
 * Testcase Example:  '2.00000\n10'
 *
 * Implement pow(x, n), which calculates x raised to the power n (xn).
 * 
 * Example 1:
 * 
 * 
 * Input: 2.00000, 10
 * Output: 1024.00000
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 2.10000, 3
 * Output: 9.26100
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: 2.00000, -2
 * Output: 0.25000
 * Explanation: 2-2 = 1/22 = 1/4 = 0.25
 * 
 * 
 * Note:
 * 
 * 
 * -100.0 < x < 100.0
 * n is a 32-bit signed integer, within the range [−231, 231 − 1]
 * 
 * 
 */
class Solution {
   double helper(double x, long long n, double acc) {
      if (n == 0) return acc;
      if (n % 2 == 0) return helper(x * x, n / 2, acc);
      else            return helper(x, n - 1, x * acc);
   }
public:
    double myPow(double x, long long n) {
       if (n < 0) {
          n = -n;
          x = 1 / x;
       }

       return helper(x, n, 1);
    }
};


/*
TESTS
2.00000
-2
2.00000
2
2.00000
1
2.00000
3
1.00000
-2147483648
*/
