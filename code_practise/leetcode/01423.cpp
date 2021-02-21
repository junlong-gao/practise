class Solution {
#define V vector
public:
   int maxScore(vector<int>& cardPoints, int k) {
      int total = 0;
      V<int> pfx{0};
      for (auto e : cardPoints) {
         pfx.push_back(pfx.back() + e);
         total += e;
      }

      int ret = 0;
      int l = cardPoints.size() - k;
      for (int i = 0; i + l < pfx.size(); ++i) {
         ret = max(ret, total - (pfx[l + i] - pfx[i]));
      }

      return ret;
   }
};
