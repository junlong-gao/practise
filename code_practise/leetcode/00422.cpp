/*

*/
class Solution {
 public:
  bool validWordSquare(vector<string>& words) {
    int n = words.size();
    if (n == 0) return true;
    if (words[0].size() != n) return false;
    for (int i = 0; i < n; ++i) {
      int j = 0;
      for (; j < words[i].size(); ++j) {
        if (j >= n) return false;
        if (i >= words[j].size()) return false;
        if (words[i][j] != words[j][i]) return false;
      }
      for (; j < n; ++j) {
        if (j >= n) continue;
        if (i < words[j].size()) return false;
      }
    }
    return true;
  }
};

/*
["abcd","bnrt","crmy","dtye"]
["aaaa", "aaa", "aa", "a"]
["aaaa", "aaa", "aaaa", "a"]
["aaaa", "aa", "aa"]
["aaaa", "a"]
["a", "aaaa", "a", "aaaa"]
*/
