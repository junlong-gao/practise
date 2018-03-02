/*
 * > lc submit 692.cpp
 *   ✔ Accepted
 *   ✔ 110/110 cases passed (18 ms)
 *   ✔ Your runtime beats 30.04 % of cpp submissions
 */

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
       unordered_map<string, int> f;
       for (const string & w : words) {
          f[w]++;
       }

       auto c = [&] (const string &l, const string &r) {
          if (f[l] != f[r]) {
             return f[l] < f[r];
          }

          return l > r;
       };

       set<string, decltype(c)> bag(c);

       for (const auto & wp : f) {
          bag.insert(wp.first);
          if (bag.size() > k) {
             bag.erase(bag.begin());
          }
       }

       return vector<string>(bag.rbegin(), bag.rend());
    }
};


/*
TESTS
["i", "love", "leetcode", "i", "love", "coding"]
2
["i", "aove", "leetcode", "i", "aove", "coding"]
2
*/
