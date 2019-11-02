class Solution {
    unordered_map<int, vector<int>> g;
    vector<bool> visited;
    int t = 0;
    vector<vector<int>> b;
    
    vector<int> lo, id;
    void helper(int v, int p) {
        //cout << v << endl;
        visited[v] = true;
        lo[v] = id[v] = t++;
        
        for (auto u : g[v]) {
            if (u == p) continue;
            if (visited[u]) {
                lo[v] = min(lo[v], id[u]);
            } else {
                helper(u, v);
                lo[v] = min(lo[v], lo[u]);
                //cout << v << " " << id[v] << " " << u<< " " << lo[u] << endl;
                if (id[v] < lo[u]) {
                    b.push_back({v, u});
                }
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        for (const auto& e : connections) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        visited.resize(n, false);
        lo.resize(n);
        id.resize(n);
        
        helper(0, -1);
        return b;
    }
};
