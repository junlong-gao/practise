/*
 *
 *  ✔ Accepted
 *    102/102 cases passed (5 ms)
 *    Your runtime beats 13.33 % of cpp submissions
 */
/*
 * [660] Remove 9
 *
 * https://leetcode.com/problems/remove-9/description/
 *
 * algorithms
 * Hard (49.47%)
 * Total Accepted:    3.9K
 * Total Submissions: 7.8K
 * Testcase Example:  '10'
 *
 * Start from integer 1, remove any integer that contains 9 such as 9, 19,
 * 29... 
 * 
 * So now, you will have a new integer sequence: 1, 2, 3, 4, 5, 6, 7, 8, 10,
 * 11, ...
 * 
 * Given a positive integer n, you need to return the n-th integer after
 * removing. Note that 1 will be the first integer.
 * 
 * Example 1:
 * 
 * Input: 9
 * Output: 10
 * 
 * 
 * 
 * 
 * ⁠Hint: n will not exceed 9 x 10^8.
 * 
 *
 * Digestion:
 * Rule of thumb: when counting numbers in order, calculate a table by length.
 *
 * s[k] = number of decimals without 9 of length k, k = 1, 2, 3...
 * s[1] = 9
 * s[2] = 81
 * ...
 *
 * Now, to find what is the value of nth such number, consider
 * n having the form:
 *
 * x00000...0 + beta (k 0's)
 *
 * where x is the leading digit of x.
 * so we know there are x * s[k] values, each start with 1, 2, ... x
 * and to construct n, we just need to find beta'th value, and lead it with x.
 *
 * beta is then n - x * s[k]
 *
 * To find x, we know n is a multiple of s[k] plus the beta, where beta < s[k], so
 * x = n / s[k]
 */

using ll = unsigned long long;

const ll length = 12;
class Solution {
public:
    static deque<ll> s;
    deque<ll> d;

    void find(ll n, ll k) {
       while (k >= 0 && s[k] > n) { k--; }
       if (k == 0) {
          d[k] = n;
       } else {
          d[k] = n / s[k];
          find(n % s[k], k);
       }
    }

    int newInteger(int n) {
        d.resize(length, 0);
        find(n, length);

        ll ret = 0;
        for (int i = d.size() - 1; i >= 0; --i) {
           ret = ret * 10 + d[i];
        }
        return ret;
    }
};

deque<ll> Solution::s = [&] () {
     deque<ll> dp, s;
     dp.push_back(0);
     dp.push_back(9);
     dp.push_back(8 * 9);
     s.push_back(0);
     s.push_back(9);
     s.push_back(81);

     for (ll i = 3; i <= length + 3; ++i) {
        ll v = 9 * dp.back();
        dp.push_back(v);
        s.push_back(s.back() + v);
     }

     return s;
}();

/*
 *
*/

/*
TESTS
800000000
1
2
3
9
10
11
12
100
101
102
1001
1002
1003
10000000
*/
