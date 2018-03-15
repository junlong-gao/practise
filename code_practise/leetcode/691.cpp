/*
 *   ✔ Accepted
 *   ✔ 100/100 cases passed (53 ms)
 *   ✔ Your runtime beats 64.24 % of cpp submissions
 * [691] Stickers to Spell Word
 *
 * https://leetcode.com/problems/stickers-to-spell-word/description/
 *
 * algorithms
 * Hard (34.87%)
 * Total Accepted:    3.7K
 * Total Submissions: 10.6K
 * Testcase Example:  '["with","example","science"]\n"thehat"'
 *
 * 
 * We are given N different types of stickers.  Each sticker has a lowercase
 * English word on it.
 * 
 * You would like to spell out the given target string by cutting individual
 * letters from your collection of stickers and rearranging them.
 * 
 * You can use each sticker more than once if you want, and you have infinite
 * quantities of each sticker.
 * 
 * What is the minimum number of stickers that you need to spell out the
 * target?  If the task is impossible, return -1.
 * 
 * 
 * Example 1:
 * Input:
 * ["with", "example", "science"], "thehat"
 * 
 * 
 * Output:
 * 3
 * 
 * 
 * Explanation:
 * We can use 2 "with" stickers, and 1 "example" sticker.
 * After cutting and rearrange the letters of those stickers, we can form the
 * target "thehat".
 * Also, this is the minimum number of stickers necessary to form the target
 * string.
 * 
 * 
 * Example 2:
 * Input:
 * ["notice", "possible"], "basicbasic"
 * 
 * 
 * Output:
 * -1
 * 
 * 
 * Explanation:
 * We can't form the target "basicbasic" from cutting letters from the given
 * stickers.
 * 
 * 
 * Note:
 * stickers has length in the range [1, 50].
 * stickers consists of lowercase English words (without apostrophes).
 * target has length in the range [1, 15], and consists of lowercase English
 * letters.
 * In all test cases, all words were chosen randomly from the 1000 most common
 * US English words, and the target was chosen as a concatenation of two random
 * words.
 * The time limit may be more challenging than usual.  It is expected that a 50
 * sticker test case can be solved within 35ms on average.
 * 
 * Digestion:
 * This is another brute force. The trick is to use dp to remember visited nodes
 * and use special ordering.
 *
 * Why special ordering? The solution we search for is permutation symmetric.
 * This is in general true when we search for a fessible set (set does not have
 * ordering). To reduce search space (avoid discovering same set with different
 * permutation), we enforce ordering when we pick next element into our constructed
 * solution set.
 *
 *
 */
class Solution {
   unordered_map<string, int> dp;
    int search(string t, const vector<vector<int>> &stickers) {
       //cout << t << endl;
       if (dp.count(t)) return dp[t];

       if (t.empty()) return 0;

       vector<int> mp(26, 0);
       for (auto c : t) { mp[c - 'a']++; }

       int best = INT_MAX;
       for (const auto & s : stickers) {
          if (0 == s[t[0] - 'a']) continue; // XXX enforce ordering to reduce search space

          string v;
          for (int i = 0; i < 26; ++i) {
             if (mp[i] - s[i] <= 0) continue;
             v += std::string(mp[i] - s[i], i + 'a');
          }

          auto r = search(v, stickers);
          if (r != INT_MAX) {
             best = std::min(best, 1 + r);
          }
       }

       dp[t] = best;
       return dp[t];
    }
public:
    int minStickers(vector<string>& stickers, string target) {
        vector<vector<int>> charMap;
        for (const auto & s : stickers) {
           charMap.emplace_back(26, 0);
           for (char c : s) {
              charMap.back()[c - 'a']++;
           }
        }

        int ret = search(target, charMap);
        return ( ret == INT_MAX) ? -1 : ret;
    }
};


/*
TESTS
["notice", "possible"]
"basicbasic"
["with", "example", "science"]
"thehat"
*/
