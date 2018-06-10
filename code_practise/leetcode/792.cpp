class Solution {
 public:
  int numMatchingSubseq(string S, vector<string>& words) {
    vector<vector<int> > count(256);
    for (int i = 0; i < S.length(); ++i) {
      count[S[i]].push_back(i);
    }
    int ans = 0;
    for (auto& word : words) {
      int cur = -1;
      bool found = true;
      for (int i = 0; i < word.size(); ++i) {
        // greedy
        auto it = upper_bound(count[word[i]].begin(), count[word[i]].end(), cur);
        if (it == count[word[i]].end()) {
          found = false;
          break;
        }
        cur = *it;
      }
      if (found) ans++;
    }
    return ans;
  }
};
