/*
 * [833] Bus Routes
 *
 * https://leetcode.com/problems/bus-routes/description/
 *
 * algorithms
 * Hard (30.39%)
 * Total Accepted:    1.4K
 * Total Submissions: 4.5K
 * Testcase Example:  '[[1,2,7],[3,6,7]]\n1\n6'
 *
 * We have a list of bus routes. Each routes[i] is a bus route that the i-th
 * bus repeats forever. For example if routes[0] = [1, 5, 7], this means that
 * the first bus (0-th indexed) travels in the sequence
 * 1->5->7->1->5->7->1->... forever.
 *
 * We start at bus stop S (initially not on a bus), and we want to go to bus
 * stop T. Travelling by buses only, what is the least number of buses we must
 * take to reach our destination? Return -1 if it is not possible.
 *
 *
 * Example:
 * Input:
 * routes = [[1, 2, 7], [3, 6, 7]]
 * S = 1
 * T = 6
 * Output: 2
 * Explanation:
 * The best strategy is take the first bus to the bus stop 7, then take the
 * second bus to the bus stop 6.
 *
 *
 * Note:
 *
 *
 * 1 <= routes.length <= 500.
 * 1 <= routes[i].length <= 500.
 * 0 <= routes[i][j] < 10 ^ 6.
 *
 * Digestion:
 * All stops in a route is a layer of "frontier". Use BFS to search through
 * these layers.
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
