/*
 * > leetcode submit 730.cpp
     ✔ Accepted
     ✔ 366/366 cases passed (189 ms)
     ✔ Your runtime beats 51.2 % of cpp submissions
 * [730] Count Different Palindromic Subsequences
 *
 * https://leetcode.com/problems/count-different-palindromic-subsequences/description/
 *
 * algorithms
 * Hard (35.23%)
 * Total Accepted:    2.4K
 * Total Submissions: 6.7K
 * Testcase Example:  '"bccb"'
 *
 *
 * Given a string S, find the number of different non-empty palindromic
 * subsequences in S, and return that number modulo 10^9 + 7.
 *
 * A subsequence of a string S is obtained by deleting 0 or more characters
 * from S.
 *
 * A sequence is palindromic if it is equal to the sequence reversed.
 *
 * Two sequences A_1, A_2, ... and B_1, B_2, ... are different if there is some
 * i for which A_i != B_i.
 *
 *
 * Example 1:
 *
 * Input:
 * S = 'bccb'
 * Output: 6
 * Explanation:
 * The 6 different non-empty palindromic subsequences are 'b', 'c', 'bb', 'cc',
 * 'bcb', 'bccb'.
 * Note that 'bcb' is counted only once, even though it occurs twice.
 *
 *
 *
 * Example 2:
 *
 * Input:
 * S = 'abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba'
 * Output: 104860361
 * Explanation:
 * There are 3104860382 different non-empty palindromic subsequences, which is
 * 104860361 modulo 10^9 + 7.
 *
 *
 *
 * Note:
 * The length of S will be in the range [1, 1000].
 * Each character S[i] will be in the set {'a', 'b', 'c', 'd'}.
 *
 * Digestion
 * 1. Start simple, consider 
 *    dp[i][j] = # all distinct palindroms in the substring s[i...j] (left right
 *    inclusive.
 *    The difficulty becomes apparent when handling the case s[i] == s[j]:
 *    when s[i] == s[j], we consider all distinct palindroms in s[i...j], and
 *    they come in two favors:
 *    1. they start and end with s[i] (s[j]).
 *    2. they start and end with something else.
 *    then dp[i][j] = type 1 + type 2
 *    for the type 1 collection, there is a nice recursive structure:
 *    take any palindrom of type 1 with length > 2, strip off the first s[i] and last
 *    s[j], the remaining non empty string is a palindrom belonging to dp[i + 1][j - 1].
 *    More over, we argue that for all type 1 collection with length > 2, we strip the first
 *    and last off, the remaining collection of palindroms are also distinct (because
 *    the original collection is distinct, you are just stripping off the first and last char).
 *    Therefore, for any type 1 palin in dp[i][j] with length > 2, there exists an
 *    unique palin in dp[i + 1][j - 1],
 *    so looks like we can do dp[i][j] = dp[i + 1][j - 1] + type 2
 *
 *    But we cannot do this addition with type 2 because our definition of dp[i][j]
 *    does not carry the information of starting with what character.
 *
 * 2. Refining the state
 *    To mitigate the difficulty of finding type 2, we refine the state def
 *    to be
 *    dp[i][j][c] = # all distinct palindroms in the substring s[i...j] (left right
 *    inclusive) such that they start (and end) in char c.
 *    then dp[i][j] = sum {c = 'a', 'b', 'c', 'd'} dp[i][j][c]
 *    Note, however, changing the state definition by refining it usually
 *    leads to a different (and easier) recursive structure:
 *    let len([i, j]) >= 3 (for len 1 and 2 we handle them as special base cases)
 *    dp[i][j][c] = match s[i] and s[j] with
 *                | s[i] == s[j] == c -> sum {c = 'a', 'b', 'c', 'd'} dp[i + 1][j - 1][c] + 1 (for case c) + 1 (for case cc)
 *                  this comes from exactly the same strip off argument above.
 *                | s[i] == c         -> dp[i][j-1][c]
 *                  only the first char matches c, so the solution of dp[i][j][c] must be the same as dp[i][j - 1][c] since last
 *                  char s[j] does not contribute to counting.
 *                | s[j] == c         -> dp[i + 1][j][c]
 *                  only the last char matches c, so the solution of dp[i][j][c] must be the same as dp[i + 1][j][c] since first
 *                  char s[j] does not contribute to counting.
 *                | _                 -> dp[i + 1][j - 1][c]
 *                  neither s[i] and s[j] matches, so the total number of distinct palindroms in this window starting with c must all
 *                  come from dp[i + 1][j - 1][c]
 *
 *    for case [i, i], one single char match c
 *    for case [i, i + 1], three possibilities: 2(cc), 1(c!c or !cc), 0(!c!c)
 *
 * 3. The above solution is correct, but failed memory constraint. (table or memorization does not work).
 *    The trick is finding the correct dependency graph of the solution states:
 *    to calculate a solution dp[i][j][c] of len([i, j]) = l, we just need all
 *    the dp entires of len([i', j']) = l - 1 and l - 2.
 *    So instead of forming table dp[i][j][c], we consider table dp[i][l][c],
 *    where l = j - i + 1.
 *    Then we "roll" the table as we fill with increasing l from 1 to n:
 *    dp[i][l % 3][c] depends on
 *    dp[i][(l - 1) % 3][c] and dp[i][(l - 2) % 3][c]
 *
 *    In this way the memory constraint reduce to O(n) and is accepted.
 *
 *    See complete impl below.
 */
class Solution {
   int n;
   using ll = long long;
   const ll m = 1e9 + 7;
   int get(const int i) {
      return (i + 3) % 3;
   }
public:
    int countPalindromicSubsequences(string s) {
       n = s.size();
       auto dp = vector<vector<vector<ll>>>(4, vector<vector<ll>>(3, vector<ll>(n, 0)));

       for (int l = 1; l <= n; ++l) { for (int i = 0; i + l - 1 < n; ++i) { for (char c : {'a', 'b', 'c', 'd'}) {
          int j = i + l - 1;
          int idx = c - 'a';
          ll & v = dp[idx][get(l)][i];
          // base case len = 1
          if      (i == j)                         { v = (s[i] == c ? 1 : 0);                                                                }
          // base case len = 2
          else if (i == j - 1) {
               if      (s[i] == s[j] && s[i] == c) { v = 2;                                                                                  }
               else if (s[i] == c || s[j] == c)    { v = 1;                                                                                  }
               else                                { v = 0;                                                                                  }}
          // recursive len >= 3
          else {
               if (s[i] == s[j] && s[i] == c)      { v = 2; for (char c : {'a','b','c','d'}) { v = (v + dp[c - 'a'][get(l - 2)][i + 1]) % m; }}
               else if (s[i] == c)                 { v = dp[idx][get(l - 1)][i];                                                             }
               else if (s[j] == c)                 { v = dp[idx][get(l - 1)][i + 1];                                                         }
               else                                { v = dp[idx][get(l - 2)][i + 1];                                                         }}
          //cout << idx << " " << i << " " << j << " " << v << endl;
       } } }

       return [&]{ ll ret = 0; for (char c : {'a','b','c','d'}) { ret = (ret + dp[c - 'a'][get(n)][0]) % m; } return ret;}();
    }
};


/*
TESTS
"bbb"
"bccb"
"b"
"bb"
"bbbb"
"bcbcbc"
"abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba"
*/
