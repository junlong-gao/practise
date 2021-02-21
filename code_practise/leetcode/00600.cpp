/*
 * > leetcode submit 600.cpp
 *   ✔ Accepted
 *   ✔ 527/527 cases passed (15 ms)
 *   ✔ Your runtime beats 29.07 % of cpp submissions
 *
 * [600] Non-negative Integers without Consecutive Ones
 *
 * https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/description/
 *
 * algorithms
 * Hard (31.66%)
 * Total Accepted:    5.3K
 * Total Submissions: 16.8K
 * Testcase Example:  '1'
 *
 * Given a positive integer n, find the number of non-negative integers less
 * than or equal to n, whose binary representations do NOT contain consecutive
 * ones.
 * 
 * Example 1:
 * 
 * Input: 5
 * Output: 5
 * Explanation: 
 * Here are the non-negative integers 
 * 
 * 
 * Note:
 * 1 9
 * 
 * 
 * Digestion:
 * dp[n] = # desired binary string of length n
 * dp[0] = 1, dp[1] = 2, dp[2] = 3
 * dp[n] = dp[n-1] + dp[n-2]
 *
 * let n be a decomposed into binary representation:
 * 2^k_0 + 2^k_1 + 2^k_2 ... + 2^k_j
 * Then we can count each interval:
 * [0, 2^k_0)             -> dp[k_0] (count the form 0XXXXX..X, k_0's X)
 * [2^k_0, 2^k_0 + 2^k_1) -> dp[k_1] (in the form 1XXX0YYYY...Y, k_1's Y)
 * ...
 * finally, don't forget to add n itself contribution
 * [2^k_0 + 2^_k_1 ... + 2^k_j)
 *
 * The trick is, if we follow this order, we find two consecutive 1, we can
 * immediately stop and ignore the rest intervals (the rest forms are not valid).
 *
 */
class Solution {
public:
    int findIntegers(int num) {
        static const vector<int> dp = [&] {
           vector<int> dp(33, 0);
           dp[0] = 1; dp[1] = 2;
           for (int i = 2; i < 33; ++i) {
              dp[i] = dp[i-1]+dp[i-2];
           }
           return dp;
        }();

        vector<int> bv;
        int ret = 0;
        int n = num;
        int count = 0;

        while (num) {
           bv.push_back(num % 2);
           num = num / 2;
        }
        std::reverse(bv.begin(), bv.end());

        //cout << bv.size() << endl;
        for (int i = 0; i < bv.size(); ++i) {
           //cout << "i=" << i << endl;
           if (bv[i] == 1 && count < 2) {
              ret += dp[bv.size() - i - 1];
              //cout << bv.size() - i - 1 << " " << dp[bv.size() - i - 1] << endl;
           } else if (count >= 2) {
              break;
           }

           if (bv[i] == 1) {
              count++;
           } else {
              count = 0;
           }
        }

        return (count >= 2) ? ret : ret + 1;
    }
};

/*
 *
1
2
3
4
5
6
7
8
9
10
11
12
14
15
31
32
63
64
127
128
1023
1024
7
13
127
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
9
10
11
12
14
15
31
32
63
64
127
128
1023
1024
7
13
127
5
65535
65536
*/
