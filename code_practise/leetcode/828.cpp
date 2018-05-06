/*
 * [855] Unique Letter String
 *
 * https://leetcode.com/problems/unique-letter-string/description/
 *
 * algorithms
 * Hard (20.54%)
 * Total Accepted:    338
 * Total Submissions: 1.7K
 * Testcase Example:  '"ABC"'
 *
 * A character is unique in string S if it occurs exactly once in it.
 *
 * For example, in string S = "LETTER", the only unique characters are "L" and
 * "R".
 *
 * Let's define UNIQ(S) as the number of unique characters in string S.
 *
 * For example, UNIQ("LETTER") =  2.
 *
 * Given a string S, calculate the sum of UNIQ(substring) over all non-empty
 * substrings of S.
 *
 * If there are two or more equal substrings at different positions in S, we
 * consider them different.
 *
 * Since the answer can be very large, retrun the answer modulo 10 ^ 9 + 7.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: "ABC"
 * Output: 10
 * Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
 * Evey substring is composed with only unique letters.
 * Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
 *
 * Example 2:
 *
 *
 * Input: "ABA"
 * Output: 8
 * Explanation: The same as example 1, except uni("ABA") = 1.
 *
 *
 *
 *
 * Note: 0 <= S.length <= 10000.
 *
 * Digestion.
 * f[n] = sum of UNIQ(s) for all substring s end in S[n - 1]
 *
 * Now consider f[n + 1] =
 *     sum of UNIQ(s) for all substring s end in S[n]
 *  =  1 + sum of UNIQ(s + c) for all substring s end in S[n - 1]
 *     (where c = S[n])
 *
 * UNIQ(s + c) = UNIQ(s) + [if c is in s for 0 times then 1]
 *                         [if c is in s for 1 times then -1]
 *                         [if c is in s for >= 2 times then 0]
 *
 * then, easily we can see
 *  = sum of UNIQ(s + c) for all substring s end in S[n - 1]
 *  = f[n] + sum of [if c is in s for 0 times then 1]
 *                  [if c is in s for 1 times then -1]
 *                  [if c is in s for >= 2 times then 0]
 *                  for all s in prefix S[0..n) c = S[n]
 *
 * To calculate the last part efficiently, we can consider where
 * c occurs:
 * index: 0, 1, ... y, ... x, ... n - 1, n
 *                                       c
 * x is the index where c first occurs *starting from index n*
 * y is the index where c second occurs *starting from index n*
 *
 * then for substring end in S[n - 1] start from j:
 * if j is in range (x, n) -> +1 : adding c to it, c is first time
 * if j is in range (y, x) -> -1 : adding c to it, c is second time
 * if j is in range [0, y] -> 0 :  adding c to it, c is is > 2 times
 *
 * to get all these x, y information, we simply create a reversed linked list:
 * each position tracks its nearest appearance to its left.
 * see the construct of g in the code:
 *
 */
class Solution {
public:
    int uniqueLetterString(string S) {
       int n = S.length();
       long long M = 1e9 + 7;
       vector<int> f(n, 0), g(n, -1);
       unordered_map<char, int> last;
       auto add = [&](int l, int r) {
          return (static_cast<long long>(l) + static_cast<long long>(r)) % M;
       };
       auto sub  = [&](int l, int r) {
          return (static_cast<long long>(l) + M - static_cast<long long>(r)) % M;
       };

       for (int i = 0; i < n; ++i) {
          int c = S[i];
          if (last.count(c) != 0) {
             g[i] = last[c];
          }
          last[c] = i;
       }

       long long ret = 0;
       for (int i = 0; i < n; ++i) {
          if (i == 0) { f[i] = 1; }
          else {
             f[i] = add(f[i - 1], sub(i - 1, g[i]));
             int x = g[i];
             if (x != -1) {
                f[i] = sub(f[i], sub(x, g[x]));
             }
             f[i] = add(f[i], 1);
          }
          ret = add(ret, f[i]);
       }

       return ret;
    }
};


/*
TESTS
"ABC"
"ABA"
"LETTER"
"MATHEMATICALCERTAINTY"
""
"A"
*/
