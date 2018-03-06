/*
 * > leetcode submit 753.cpp
 *   ✔ Accepted
 *   ✔ 38/38 cases passed (12 ms)
 *
 * [754] Cracking the Safe
 *
 * https://leetcode.com/problems/cracking-the-safe/description/
 *
 * algorithms
 * Hard (39.54%)
 * Total Accepted:    2.7K
 * Total Submissions: 6.9K
 * Testcase Example:  '1\n1'
 *
 *
 * There is a box protected by a password.  The password is n digits, where
 * each letter can be one of the first k digits 0, 1, ..., k-1.
 *
 * You can keep inputting the password, the password will automatically be
 * matched against the last n digits entered.
 *
 * For example, assuming the password is "345", I can open it when I type
 * "012345", but I enter a total of 6 digits.
 *
 * Please return any string of minimum length that is guaranteed to open the
 * box after the entire string is inputted.
 *
 *
 * Example 1:
 *
 * Input: n = 1, k = 2
 * Output: "01"
 * Note: "10" will be accepted too.
 *
 *
 *
 * Example 2:
 *
 * Input: n = 2, k = 2
 * Output: "00110"
 * Note: "01100", "10011", "11001" will be accepted too.
 *
 *
 *
 * Note:
 *
 * n will be in the range [1, 4].
 * k will be in the range [1, 10].
 * k^n will be at most 4096.
 *
 *
 * Digestion:
 * de brujin graph
 * Use back track to find a Hamiltonian cycle
 */
class Solution {
   unordered_set<string> nodes;
   int target;
   string ret;
   int n, k;

   bool dfs(string cur) {
      if (nodes.size() == target) {
         return true;
      }

      cur = cur.substr(1, cur.size() - 1);
      for (int i = 0; i < k; ++i) {
         char c = i + '0';
         string next = cur + c;
         if (nodes.count(next) == 0) {
            nodes.insert(next);
            ret += c;
            if (dfs(next)) return true;
            // back track
            ret.pop_back();
            nodes.erase(next);
         }
      }

      return false;
   }
public:
    string crackSafe(int nn, int kk) {
        n = nn, k = kk;
        target = 1;
        for (int i = 0; i < n; ++i) {
           ret += '0';
           target = target * k;
        }
        nodes.insert(ret);
        assert(dfs(ret));
        return ret;
    }
};


/*
TESTS
1
1
2
2
3
3
*/
