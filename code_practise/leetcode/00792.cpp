static int x=[](){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
  int numMatchingSubseq(string S, vector<string>& words) {
    array<vector<int>, 26> buckets;
    for (int i = 0; i < words.size(); ++i) {
        reverse(words[i].begin(), words[i].end());
        buckets[words[i].back() - 'a'].push_back(i);
    }
      int matched = 0;
      for (int i = 0; i < S.size(); ++i) {
          int nc = S[i] - 'a';
         if (buckets[nc].empty()) { continue; }
         vector<int> t;
         swap(t, buckets[nc]);
         for (auto idx : t) {
           words[idx].pop_back();
           if (words[idx].empty()) { matched++; }
           else {
             buckets[words[idx].back() - 'a'].push_back(idx);
            }
        }
      }
      return matched;
  }
};
