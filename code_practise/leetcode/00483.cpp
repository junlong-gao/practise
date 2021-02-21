/*
 * > leetcode submit 483.cpp
 *   ✔ Accepted
 *   ✔ 106/106 cases passed (5 ms)
 *   ✔ Your runtime beats 33.54 % of cpp submissions
 *
 * [483] Smallest Good Base
 *
 * https://leetcode.com/problems/smallest-good-base/description/
 *
 * algorithms
 * Hard (33.65%)
 * Total Accepted:    6.7K
 * Total Submissions: 19.8K
 * Testcase Example:  '"13"'
 *
 * For an integer n, we call k>=2 a good base of n, if all digits of n base k
 * are 1.
 * Now given a string representing n, you should return the smallest good base
 * of n in string format. 
 * 
 * Example 1:
 * 
 * Input: "13"
 * Output: "3"
 * Explanation: 13 base 3 is 111.
 * 
 * 
 * 
 * Example 2:
 * 
 * Input: "4681"
 * Output: "8"
 * Explanation: 4681 base 8 is 11111.
 * 
 * 
 * 
 * Example 3:
 * 
 * Input: "1000000000000000000"
 * Output: "999999999999999999"
 * Explanation: 1000000000000000000 base 999999999999999999 is 11.
 * 
 * 
 * 
 * Note:
 * 
 * The range of n is [3, 10^18].
 * The string representing n is always valid and will not have leading zeros.
 * 
 * Digestion:
 * Let d be the length of the all 1 string
 *
 * It is very difficult to find k in terms of n.
 *
 * Think in the *other* way: it is trivial to find a k in terms of d:
 * Given d, the value m(k) = sum_{0 <= i < d} k^i is a monotonic function
 * of base k. So we can quickly find the first k m(k) >= n
 *
 * This reveals the correct solution: for all d, use the binary search to find
 * k(d) so that m(k) == n.
 * And find min_{d in [2, 60]} k(d).
 * (In fact, start d with largest value 60, and move back wards, the first
 * one gives the smallest k)
 *
 * One note on binary search: think carefully before reuse the checking value.
 * The final assignment that makes you break the while loop does not follow
 * a correct value from hi. (it could be updating lo)
 */
class Solution {
   using ull = unsigned long long;
public:
    string smallestGoodBase(string n) {
        const ull target = std::stoull(n);
        for (int d = log2(target) + 1; d >= 1; --d) {
           ull lo = 1;
           ull hi = std::max(2ull, (ull)std::pow(target, 1.0 / d));  // XXX <--- this implies
           // the calculation of value start with 1 (to the dth power)
           // and pow(target, 1.0) != target....
           // also, for small input like target = 3, we need to make sure
           // the value is at least 2
           if (d == 1) {
              return std::to_string(target - 1);
           }
           while (hi - lo > 1) {
              ull mid = lo + (hi - lo) / 2;
              ull value = 1;
              for (int i = 0; i < d; ++i) {
                 value = value * mid + 1;
              }

              if (value >= target) {
                 hi = mid;
              } else {
                 lo = mid;
              }
           }

           ull value = 1;
           for (int i = 0; i < d; ++i) {
              value = value * hi + 1;
           }

           if (value == target) {
              return std::to_string(hi);
           }
        }

        assert(0);
        return "";
    }
};


/*
 *
 */

/*
TESTS
"3"
"4"
"5"
"727004545306745403"
"1000000000000000000"
"4681"
"13"
"2251799813685247"
"919818571896748567"
*/
