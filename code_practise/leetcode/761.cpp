/*
 *lcg 761
   ✔ Accepted
   ✔ 86/86 cases passed (6 ms)
   ✔ Your runtime beats 13.22 % of cpp submissions
 */
/*
 * [763] Special Binary String
 *
 * https://leetcode.com/problems/special-binary-string/description/
 *
 * algorithms
 * Hard (39.44%)
 * Total Accepted:    1.3K
 * Total Submissions: 3.2K
 * Testcase Example:  '"11011000"'
 *
 *
 * Special binary strings are binary strings with the following two
 * properties:
 *
 * The number of 0's is equal to the number of 1's.
 * Every prefix of the binary string has at least as many 1's as 0's.
 *
 * Given a special string S, a move consists of choosing two consecutive,
 * non-empty, special substrings of S, and swapping them.  (Two strings are
 * consecutive if the last character of the first string is exactly one index
 * before the first character of the second string.)
 *
 * At the end of any number of moves, what is the lexicographically largest
 * resulting string possible?
 *
 *
 * Example 1:
 *
 * Input: S = "11011000"
 * Output: "11100100"
 * Explanation:
 * The strings "10" [occuring at S[1]] and "1100" [at S[3]] are swapped.
 * This is the lexicographically largest string possible after some number of
 * swaps.
 *
 *
 *
 * Note:
 * S has length at most 50.
 * S is guaranteed to be a special binary string as defined above.
 *
 * Digestion:
 * divide and conquer:
 *    from left to right, try to decompose S into consecutive special strings
 *    greedily.
 * case 1:
 *    if string S cannot be decomposed into a form of segments ABC... where
 *    each is a special string with length >= 2 and number of segments > 0,
 *    we conclude that the swap never involves the first char and the last
 *    character.
 *    If it involves swapping a seg including the first char, then it must
 *    can be decomposed into A(with first char) then follows whatever it swaps,
 *    say B, and the rest part must either be empty or a special string.
 *    This is because AB as concat is a special string(tricky) and S is a
 *    special string, it is not hard to conclude the rest part must be a
 *    special string.
 *    Second, if it involves swapping a seg including the last char, then
 *    it must can be decomposed into XBA, where B is what swaps with A. Then
 *    we find X must be a special string as concat BA is and S is (and every
 *    prefix of X is a prefix of S).
 *
 *    Therefore, if S cannot be decomposed in the above form, we conclude
 *    the final solution must be 1 + S.substr(1, S.length() - 2) + 0.
 *
 * case 2:
 *    Now we assume S can be decomposed into the above form ABC..., where
 *    there is at least 2 segments, each is a special string. Refer this as
 *    the special string decomposition.
 *    Note that, for any swapping happen within any of A, B, C ..., it does
 *    not change that fact that A', B', C' is still special string respectively.
 *    We conclude that it is impossible to have a swap cross any two
 *    decompositions. This is because concat of two special string is still a
 *    special string and the decomposition is greedy, so we would decompose
 *    into AB'B... instead of AB...
 *
 * Combining case 1 and 2 we see this can be solved via recursion:
 *    for case 1: 1 + solve(S.substr(1, S.length() - 2)) + 0
 *    for case 2: solve each decomposition, then as any permutation can be done
 *    via swapping adjacent swaps, we simply sort all subproblem's result to get
 *    the largest sequence.
 *
 *
 *
 */
class Solution {
public:
    string makeLargestSpecial(string S) {
       if (S.size() <= 2) return S;

       vector<string> seg;
       int count = 0, last = 0;
       for (int i = 0; i < S.size(); ++i) {
          if (S[i] == '1') count++;
          else count --;
          if (count == 0) {
             seg.push_back(S.substr(last, i - last + 1));
             last = i + 1;
          }
       }

       assert(seg.size() >= 1);
       if (seg.size() == 1) {
          // we cannot decompose it into more special strings
          return '1' + makeLargestSpecial(S.substr(1, S.length() - 2)) + '0';
       }

       // divide and conquer
       for (string & s : seg) {
          s = makeLargestSpecial(s);
       }

       sort(seg.begin(), seg.end(),
            [](const string& l, const string & r) {
               return r < l;
            });

       string ret;
       for (const string & s : seg) {
          ret += s;
       }

       return ret;
    }
};

/*
 *
*/

/*
TESTS
"11011000"
"110110110000"
"11110000"
"10101010"
*/
