/*
All stops in a route is a layer of "frontier". Use BFS to search through these layers.
*/
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
      unordered_map<int, unordered_set<int>> in_routes;
      // original representation is too slow if a route has too many duplication
      unordered_map<int, unordered_set<int>> frontiers;
      for (int i = 0; i < routes.size(); ++i) {
        for (int j = 0; j < routes[i].size(); ++j) {
          in_routes[routes[i][j]].insert(i);
          frontiers[i].insert(routes[i][j]);
        }
      }
      
      deque<pair<int, int>> q;
      unordered_set<int> visited;
      q.push_back({S, 0});
      visited.insert(S);
      while (!q.empty()) {
        auto top = q.front(); q.pop_front();
        if (top.first == T) return top.second;
        
        // how to speed the following up?
        for (const auto & r : in_routes[top.first]) {
          for (const auto & stop : frontiers[r]) {
            if (visited.count(stop) == 0) {
              q.push_back({stop, top.second + 1});
              visited.insert(stop);
            }
          }
        }
      }
      
      return -1;
    }
};
