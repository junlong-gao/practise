/*
 * > lcg 248
 *   ✔ Accepted
 *   ✔ 16/16 cases passed (2 ms)
 *   ✔ Your runtime beats 72.41 % of cpp submissions
 */
/*
 * [248] Strobogrammatic Number III
 *
 * https://leetcode.com/problems/strobogrammatic-number-iii/description/
 *
 * algorithms
 * Hard (32.80%)
 * Total Accepted:    11.6K
 * Total Submissions: 35.2K
 * Testcase Example:  '"50"\n"100"'
 *
 * A strobogrammatic number is a number that looks the same when rotated 180
 * degrees (looked at upside down).
 *
 * Write a function to count the total strobogrammatic numbers that exist in
 * the range of low <= num <= high.
 *
 * For example,
 * Given low = "50", high = "100", return 3. Because 69, 88, and 96 are three
 * strobogrammatic numbers.
 *
 * Note:
 * Because the range might be a large number, the low and high numbers are
 * represented as string.
 *
 */
class Solution {
public:
    int strobogrammaticInRange(string low, string high) {
       const int n = high.length();
       const int digit = 10;
       vector<vector<int>> dp(n + 1, vector<int>(digit, 0));
       unordered_set<int> alpha {0, 1, 6, 8, 9};
       unordered_set<int> beta {0, 1, 8};
       const unordered_map<int, int> mirror {
          {0, 0},
          {1, 1},
          {6, 9},
          {8, 8},
          {9, 6},
       };

       for (int i = 1; i <= n; ++i) {
          if (i == 1) {
             for (int k : beta) {
                dp[i][k] = 1;
             }
          } else if (i == 2) {
             for (int k : alpha) {
                dp[i][k] = 1;
             }
          } else {
             for (int k : alpha) {
                for (int kk : alpha) {
                   dp[i][k] += dp[i - 2][kk];
                }
             }
          }
       }

       /*
       for (int i = 1; i <= n; ++i) {
          for (int j = 0; j <= 9; ++j) {
             cout << dp[i][j] << " ";
          }
          cout << endl;
       }
       */

       auto count = [&](string &m) {
          if (m == "0") return 0;
          int ret = 0;
          for (int l = 1; l < m.length(); ++l) {
             if (l == 1) {
                for (int k : beta) {
                   if (k == 0) continue;
                   ret += dp[l][k];
                }
             } else {
                for (int k : alpha) {
                   if (k == 0) continue;
                   ret += dp[l][k];
                }
             }
          }

          for (int i = 0; static_cast<int>(m.length()) - 2 * i > 0; ++i) {
             int l = m.length() - 2 * i;
             int lead = m[i] - '0';
             if (i == 0) {
                for (int j = 1; j < lead; ++j) {
                   ret += dp[l][j];
                }
             } else {
                if (alpha.count(m[i - 1] - '0') == 0) break;
                for (int j = 0; j < lead; ++j) {
                   ret += dp[l][j];
                }
             }
          }

          // we have checked all < ABCD0000
          // the final case is the last construction
          // ABCDD'C'B'A'

          string target = m.substr(0, m.length() / 2);
          //cout << target << endl;
          if (m.length() % 2 == 1) {
             if (beta.count(m[m.length() / 2] - '0') == 0) {
                return ret + 1;
             }

             target.push_back(m[m.length() / 2]);
          }

          for (int i = m.length() / 2 - 1; i >= 0 ; --i) {
             if (mirror.count(m[i] - '0') == 0) {
                return ret + 1;
             }
             target.push_back(mirror.at(m[i] - '0') + '0');
          }

          //cout << target << endl;
          int fix = 1;
          int eqCount = 0;
          for (int i = 0; i < target.size(); ++i) {
             if (target[i] > m[i]) {
                fix = 0;
                break;
             }
          }

          if (target == m) fix = 0;

          return ret + 1 + fix;
       };

       auto check = [&](string &l) {
          for (int i = 0; static_cast<int>(l.length()) - 1 - i >= i; ++i) {
             int digit = l[i] - '0';
             int mirrorDigit = l[l.length() - 1 - i] - '0';
             //cout << digit << " " << mirrorDigit << endl;
             if (mirror.count(digit) == 0) return 0;
             if (mirrorDigit != mirror.at(digit)) return 0;
          }

          return 1;
       };

       //cout  << "@@@" << count(high) << " " << count(low) << "@@@" << endl;
       int ret = count(high) - count(low) + check(high);
       return ret >= 0 ? ret : 0;
    }
};


/*
"0"
"1"
"0"
"2"
"0"
"8"
"0"
"0"
"0"
"1"
"0"
"2"
"0"
"3"
"0"
"4"
"0"
"5"
"0"
"6"
"0"
"7"
"0"
"8"
"0"
"9"
"0"
"10"
"0"
"42"
"0"
"69"
"0"
"100"
"0"
"101"
"0"
"700"
"0"
"50"
"0"
"100"
"50"
"100"
"50"
"101"
"100"
"50"
"0"
"9695"
"0"
"9695"
"0"
"1111"
"0"
"1112"
"0"
"11111"
"0"
"11112"
"0"
"11912"
"0"
"9697"
"0"
"11112"
 */

/*
TESTS
"0"
"1"
"0"
"2"
"0"
"8"
"0"
"0"
"0"
"1"
"0"
"2"
"0"
"3"
"0"
"4"
"0"
"5"
"0"
"6"
"0"
"7"
"0"
"8"
"0"
"9"
"0"
"10"
"0"
"9695"
"0"
"9697"
"0"
"11112"
"0"
"11912"
"0"
"1"
"0"
"2"
"0"
"8"
"0"
"0"
"0"
"1"
"0"
"2"
"0"
"3"
"0"
"4"
"0"
"5"
"0"
"6"
"0"
"7"
"0"
"8"
"0"
"9"
"0"
"10"
"0"
"42"
"0"
"69"
"0"
"100"
"0"
"101"
"0"
"700"
"0"
"50"
"0"
"100"
"50"
"100"
"50"
"101"
"100"
"50"
"0"
"9695"
"0"
"9695"
"0"
"1111"
"0"
"1112"
"0"
"11111"
"0"
"11112"
"0"
"11912"
"0"
"9697"
"0"
"11112"
*/
