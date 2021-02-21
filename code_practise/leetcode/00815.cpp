#include <bits/stdc++.h>

class Solution {
    template <typename T>
    using v_t = vector<T>;
    
    template <typename T, typename R>
    using hm_t = unordered_map<T, R>;
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (S == T) return 0;
        hm_t<int, v_t<int>> rl;
        for (int i = 0; i < routes.size(); ++i) {
          for (int j = 0; j < routes[i].size(); ++j) {
            rl[routes[i][j]].push_back(i);
          }
        }
          
        deque<int> q;
        unordered_set<int> visited;
        
        int dis = 0;
        q.push_back(S);
        while (q.size()) {
            dis++;
            int s = q.size();
            for (int i = 0; i < s; ++i) {
                int bs = q.front(); q.pop_front();
                for (auto r : rl[bs]) {
                    if (visited.count(r)) {
                        continue;
                    }
                    
                    visited.insert(r);
                    for (auto nbs : routes[r]) {
                       if (nbs == T) return dis;
                       q.push_back(nbs);
                    }
                }
                
            }
        }
        
        return -1;
    }
};
