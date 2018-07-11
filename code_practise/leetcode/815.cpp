#include <bits/stdc++.h>
using namespace std;

/*
1. table : from bus stop to route index
2. visited nodes
3. current frontier

init current frontier with S
mark S to be visited
dist = 0

while frontier is not empty
  for all nodes in the frontier:
    get top; pop top
    for all route in table[top]
      for all nodes in route
        if node is not visited
          if node is destination
            return dist + 1
          push node into queue
      route.clear()
    
  dist += 1
*/
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        unordered_map<int, vector<int>> table;
      for (int i = 0; i < (int)routes.size(); ++i) {
        for (auto busStop : routes[i]) {
          table[busStop].push_back(i);
        }
      }
      
      unordered_set<int> visited;
      deque<int> frontier;
      int dist = 0;
      if (S == T) return dist;
      // init
      frontier.push_back(S);
      visited.insert(S);
      
      while(frontier.size()) {
        deque<int> t;
        swap(t, frontier);
        while (t.size()) {
          auto top = t.front(); t.pop_front();
          for (auto &routeIdx : table[top]) {
            for (auto &s : routes[routeIdx]) {
              if (visited.count(s) == 0) {
                if (s == T) {
                  return dist + 1;
                }
                visited.insert(s);
                frontier.push_back(s);
              }
            }
            routes[routeIdx].clear();
          }
        }
        dist++;
      }
      
      // cannot find T
      return -1;
    }
};

// To execute C++, please define "int main()"
int main() {
  {
    Solution s;
    vector<vector<int>> routes {
      {1, 2, 7},
      {3, 6, 7},
    };
    int S = 1; int T = 1;
    int expected = 0;
    int ret = s.numBusesToDestination(routes, S, T);
    cout << "got " << ret << endl;
    assert(ret == expected);
  }
  {
    Solution s;
    vector<vector<int>> routes {
      {1, 2, 7},
      {3, 6, 7},
    };
    int S = 1; int T = 6;
    int expected = 2;
    int ret = s.numBusesToDestination(routes, S, T);
    cout << "got " << ret << endl;
    assert(ret == expected);
  }
  {
    Solution s;
    vector<vector<int>> routes {
      {1, 2, 3},
      {1, 4, 5},
    };
    int S = 1; int T = 5;
    int expected = 1;
    int ret = s.numBusesToDestination(routes, S, T);
    cout << "got " << ret << endl;
    assert(ret == expected);
  }
  {
    Solution s;
    vector<vector<int>> routes {
      {1, 2, 3},
      {6, 4, 5},
    };
    int S = 1; int T = 5;
    int expected = -1;
    int ret = s.numBusesToDestination(routes, S, T);
    cout << "got " << ret << endl;
    assert(ret == expected);
  }
  {
    Solution s;
    vector<vector<int>> routes {
      {1, 2, 3},
      {3, 4, 5},
      {5, 6, 7},
      {2, 7},
    };
    int S = 1; int T = 7;
    int expected = 2;
    int ret = s.numBusesToDestination(routes, S, T);
    cout << "got " << ret << endl;
    assert(ret == expected);
  }
  return 0;
}
