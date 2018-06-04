/*

Inspired by the tsp problem, considering state:
(currentCities, pos)
where currentCities is a set of cities on the current path, pos is the last of
the cities visited.

We cannot use a dp solution in tsp as we can visit same city multiple times.
Also, there is no trivial recursive solution for deriving a solution for
(currentCities, pos)
from its smaller instance, as you can easily run into cycles since you can visit
a city multiple times:
({1, 2, 0}, 0) -> ({1, 0, 2}, 2) -> ({1, 2, 0}, 0)
if city 0 and 2 are connected,

however, we know the starting states:
({i}, i)
and the finishing states
({0, 1, … n - 1), i)
and the edges between the states:
(cur, i) -> (cur \union {j}, j) if and only if there is a path between cities i
and j
and we would like to find a shortest path between any source states and target
states, since
a path length represents a cost for a particular path from some starting city to
some end city.

instead of deriving a recursive solution for the original problem, we can simply
run bfs over the derived graph to find a shortest path, and then it is our
solution.

*/
class Solution {
 public:
  int shortestPathLength(vector<vector<int>>& graph) {
    int n = graph.size();
    if (graph[0].empty()) return 0;
    vector<vector<bool>> visited(1 << n, vector<bool>(n, false));
    struct S {
      int cities, pos, cost;
    };
    deque<S> q;
    for (int i = 0; i < n; ++i) {
      q.push_back(S{1 << i, i, 0});
      visited[1 << i][i] = true;
    }
    int best = INT_MAX;
    int all = (1 << n) - 1;
    while (!q.empty()) {
      auto top = q.front();
      q.pop_front();
      for (auto next : graph[top.pos]) {
        int nextCities = top.cities | (1 << next);
        if (visited[nextCities][next] == true) continue;
        visited[nextCities][next] = true;
        if (nextCities == all)
          best = min(best, top.cost + 1);
        else {
          q.push_back(S{nextCities, next, top.cost + 1});
        }
      }
    }
    return best;
  }
};
