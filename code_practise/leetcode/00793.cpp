/*
 * lcg 793
 * Accepted
 * 44/44 cases passed (3 ms)
 * [WARN] Failed to get submission beat ratio
 *
 * [809] Preimage Size of Factorial Zeroes Function
 *
 * https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/description/
 *
 * algorithms
 * Hard (38.03%)
 * Total Accepted:    1.3K
 * Total Submissions: 3.3K
 * Testcase Example:  '0'
 *
 * Let f(x) be the number of zeroes at the end of x!. (Recall that x! = 1 * 2 *
 * 3 * ... * x, and by convention, 0! = 1.)
 * 
 * For example, f(3) = 0 because 3! = 6 has no zeroes at the end, while f(11) =
 * 2 because 11! = 39916800 has 2 zeroes at the end. Given K, find how many
 * non-negative integers x have the property that f(x) = K.
 * 
 * 
 * Example 1:
 * Input: K = 0
 * Output: 5
 * Explanation: 0!, 1!, 2!, 3!, and 4! end with K = 0 zeroes.
 * 
 * Example 2:
 * Input: K = 5
 * Output: 0
 * Explanation: There is no x such that x! ends in K = 5 zeroes.
 * 
 * 
 * Note:
 * 
 * 
 * K will be an integer in the range [0, 10^9].
 * 
 * 
 */
class Solution {
   using ll = long long;
public:
    int preimageSizeFZF(int K) {
       auto find = [] (ll k) {
          auto f = [] (ll x) {
             ll t = x;
             ll count = 0;
             while (x > 0) {
                x = x / 5;
                count += x;
             }

             return count;
          };

          ll lo = 0ul, hi = 5ul * k;
          while (hi - lo > 1) {
             ll mid = lo + (hi - lo) / 2;
             if (f(mid) >= k) {
                hi = mid;
             } else {
                lo = mid;
             }
          }


          return hi;
       };

       return find(K + 1) - find(K);
    }
};

/*
 */
/*
TESTS
1
2
3
4
5
6
7
8
1000000000
*/
