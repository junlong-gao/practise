class Solution {
public:
    bool isPossible(vector<int>& nums) {
      unordered_map<int, priority_queue<int, vector<int>, greater<int>>> segs;
      for (const auto & v : nums) {
        if (segs.count(v - 1) == 0) {
          segs[v].push(1);
        } else {
          auto t = segs[v - 1].top();
          segs[v - 1].pop();
          if (segs[v - 1].empty()) {
            segs.erase(v - 1);
          }
          segs[v].push(t + 1);
        }
      }
      for (auto &pr : segs) {
        while (pr.second.size()) {
          if (pr.second.top() < 3) {
            return false;
          }
          pr.second.pop();
        }
      }
      return true;
    }
};
