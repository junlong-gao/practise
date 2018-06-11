class Solution {
 public:
  int integerReplacement(int n) {
    unordered_set<long long> visited;
    deque<pair<long long, int>> q;
    q.push_back({n, 0});
    visited.insert(n);
    while (q.size()) {
      auto top = q.front();
      q.pop_front();
      if (top.first == 1) return top.second;
      if (top.first % 2) {
        if (visited.count(top.first + 1) == 0) {
          q.push_back({top.first + 1, top.second + 1});
        }
        if (visited.count(top.first - 1) == 0) {
          q.push_back({top.first - 1, top.second + 1});
        }
      } else {
        if (visited.count(top.first / 2) == 0) {
          q.push_back({top.first / 2, top.second + 1});
        }
      }
    }
    return -1;
  }
};

