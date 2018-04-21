/*
 * ✔ Accepted
 * ✔ 201/201 cases passed (19 ms)
 * ✔ Your runtime beats 92.75 % of cpp submissions
 */
/*
 * [664] Strange Printer
 *
 * https://leetcode.com/problems/strange-printer/description/
 *
 * algorithms
 * Hard (34.06%)
 * Total Accepted:    5K
 * Total Submissions: 14.6K
 * Testcase Example:  '"aaabbb"'
 *
 *
 * There is a strange printer with the following two special requirements:
 *
 *
 * The printer can only print a sequence of the same character each time.
 * At each turn, the printer can print new characters starting from and ending
 * at any places, and will cover the original existing characters.
 *
 *
 *
 *
 *
 * Given a string consists of lower English letters only, your job is to count
 * the minimum number of turns the printer needed in order to print it.
 *
 *
 * Example 1:
 *
 * Input: "aaabbb"
 * Output: 2
 * Explanation: Print "aaa" first and then print "bbb".
 *
 *
 *
 * Example 2:
 *
 * Input: "aba"
 * Output: 2
 * Explanation: Print "aaa" first and then print "b" from the second place of
 * the string, which will cover the existing character 'a'.
 *
 *
 *
 * Hint: Length of the given string will not exceed 100.
 *
 * Digestion:
 * Fact 1:
 * let str[i] == c for range str[i, j]
 * There exists an opt that first prints the first few character c
 *
 * Proof:
 * Consider a printing order that does not print str[i] first, rather printing
 * it later:
 * alpha op:{ (i, k') -> c } beta
 * alpha is a sequence of print does not touch str[i], then op prints first
 * a few c (k' times) (the notation (i, k') -> c means print at i, for k' times c), then beta.
 *
 * We can reorder it into the following with exactly the same print count:
 * op:{ (j, k') -> c } alpha' beta
 * 
 * Where alpha' is obtained by taking each op in alpha:
 * op = { (l, m) -> x}
 * into:
 * op' = { (max(l, i + k), min(m, l + m - i + k)) -> x}
 * (so basically just mask off the part that overlaps [i, i + k - 1])
 *
 * and achieving the same final str[i, j]
 *
 * Fact 2:
 * if c == str[i] == str[j]
 * then opt[i, j] == opt[i, j - 1]
 * Proof:
 * From fact 1, we know there is a opt[i, j] that first prints first char c.
 * We can safely replace it with printing entire str[i, j] with c to cover
 * the last c, as all other steps get subsequent print overwritten. 
 * This gives us a printing solution for str[i, j - 1]:
 * So opt[i, j - 1] <= opt[i, j].
 *
 * From fact 1, we know there is a opt[i, j - 1] that first prints first char c.
 * We can safely replace it with printing entire str[i, j] with c to cover
 * the last c, as all other steps get subsequent print overwritten. 
 * This gives us a printing solution for str[i, j]:
 * So opt[i, j] <= opt[i, j - 1].
 *
 * Therefore opt[i, j] == opt[i, j - 1]
 *
 *
 * From fact 1 and 2 we can develop the following opt structure:
 *
 * Let c be the str[i] in str[i, j]
 * We know there is an opt first prints str[i] for m times,
 *
 * case 1 (str[i] == str[j]):
 *    print entire str[i]
 *    opt[i, j - 1]
 *
 * case 2 (m == k - i + 1):
 *    Some combination of opt[i, k] + opt[k + 1, j]
 */
class Solution {
    vector<vector<int>> dp;
    string str;

    int helper(int i, int j) {
       //cout << i << " " << j << endl;
       if (i == j) return 1;
       if (i > j) return 0;
       if (dp[i][j] != INT_MAX) return dp[i][j];

       int &ans = dp[i][j];
       ans = j - i + 1;
       if (str[i] == str[j]) {
          ans = std::min(ans, helper(i, j - 1));
          return ans;
       }

       for (int k = i; k < j; ++k) {
          ans = std::min(ans, helper(i, k) + helper(k + 1, j));
       }

       return ans;
    }

public:
    int strangePrinter(string s) {
       int n = s.length();
       if (n == 0) return 0;
       if (n == 1) return 1;
       dp = vector<vector<int>>(n, vector<int>(n, INT_MAX));
       std::swap(s, str);

       // dedup to speed up
       int i = 0;
       int j = 0;
       while (i < n) {
          while (i < n && str[i] == str[j]) i++;
          j++;
          str[j] = str[i];
       }
       n = j;
       str = str.substr(0, n);
       //cout << str << endl;
       return helper(0, n - 1);
    }
};

/*
 *
"aba"
"aaabbb"
"abcdefg"
"aabbaba"
"badcbcabdbdcdbabd"
"badcbcabd"
"bacbcabd"
"bacbcab"
"aaabbb"
"aabbaba"
"badcbcabdbdcdbabd"
"aaa"
"aabbaba"
"bacbcab"
"badcbcabdbdcdbab"
"aaabbb"
"bacbcab"
"aabbaba"
"badcbcabdbdcdbab"
"badcbcabdbdcdba"
"aba"
"aaabbb"
"abcdefg"
"aabbaba"
"badcbcabdbdcdbabd"
"badcbcabd"
"bacbcabd"
"bacbcab"
"aaabbb"
"aabbaba"
"badcbcabdbdcdbabd"
"aaa"
"aabbaba"
"bacbcab"
"bacbca"
"babdbdcd"
*/

/*
TESTS
"dbdcd"
"badcbcabdbdcdbabd"
"aba"
"aaabbb"
"abcdefg"
"aabbaba"
"badcbcabdbdcdbabd"
"badcbcabd"
"bacbcabd"
"bacbcab"
"aaabbb"
"aabbaba"
"badcbcabdbdcdbabd"
"aaa"
"aabbaba"
"bacbcab"
"badcbcabdbdcdbab"
"aaabbb"
"bacbcab"
"aabbaba"
"badcbcabdbdcdbab"
"badcbcabdbdcdba"
"aba"
"aaabbb"
"abcdefg"
"aabbaba"
"badcbcabdbdcdbabd"
"badcbcabd"
"bacbcabd"
"bacbcab"
"aaabbb"
"aabbaba"
"badcbcabdbdcdbabd"
"aaa"
"aabbaba"
"bacbcab"
"bacbca"
"babdbdcd"
*/
