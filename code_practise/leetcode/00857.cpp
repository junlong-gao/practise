class Solution {
    struct cmp {
       bool operator()(const pair<int, int> &l, const pair<int, int> &r) const {
           if (l.first != r.first) {
               return l.first > r.first;
           }
           return l.second < r.second;
       }
    };
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
      vector<pair<double, int>> ratio;
      int n = quality.size();
      vector<int> sums(n, 0);
      double lo = static_cast<int>(numeric_limits<int>::max());
      double hi = static_cast<int>(numeric_limits<int>::max());

      for (int i = 0; i < n; ++i) {
         lo = min(lo, static_cast<double>(wage[i]));
        ratio.push_back({static_cast<double>(wage[i]) / static_cast<double>(quality[i]), quality[i]});
      }

      sort(ratio.begin(), ratio.end(),
      [&](const pair<double, int> l, const pair<double, int> r) {
        return l.first > r.first;
      });

      set<pair<int, int>, cmp> bag;
      int t = 0;
      for (int i = 0; i < K; ++i) {
          t += ratio[n - 1 - i].second;
          bag.insert({ratio[n - 1 - i].second, n - 1 - i});
      }
      sums[n - K] = t;
      assert(bag.size());
      for (int i = n - 1 - K; i >= 0; --i) {
          if (ratio[i].second < bag.begin()->first) {
              t -= bag.begin()->first;
              t += ratio[i].second;
              bag.erase(bag.begin());
              bag.insert({ratio[i].second, i});
          }
          sums[i] = t;
      }

      double best = numeric_limits<double>::max();
      for (int i = 0; i <= n - K; ++i) {
         best = min(best, ratio[i].first * sums[i]);
      }

      return best;
    }
};
