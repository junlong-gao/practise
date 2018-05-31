/*
abcd

*/
class Solution {
 public:
  string findReplaceString(string S, vector<int>& indexes,
                           vector<string>& sources, vector<string>& targets) {
    unordered_map<int, int> m;
    for (int i = 0; i < indexes.size(); ++i) {
      m[indexes[i]] = i;
    }
    string ret;
    for (int i = 0; i < S.size();) {
      if (m.count(i) == 0) {
        ret.push_back(S[i]);
        ++i;
      } else {
        int idx = m[i];
        if (S.substr(indexes[idx], sources[idx].size()) != sources[idx]) {
          ret.push_back(S[i]);
          ++i;
          continue;
        }
        ret += targets[idx];
        i += sources[idx].size();
      }
    }
    return ret;
  }
};
