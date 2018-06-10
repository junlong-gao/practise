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
        auto it = upper_bound(S[word[i]].begin(), S[word[i]].end(), cur);
        if (it == S[word[i]].end()) {
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



