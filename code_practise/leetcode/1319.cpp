class Solution {
    void flood(vector<bool>& visited, int v, vector<vector<int>>& g) {
        for (auto u : g[v]) {
            if (!visited[u]) {
                visited[u] = true;
                flood(visited, u, g);
            }
        }
    }
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        vector<vector<int>> g(n);
        int edge = 0;
        for (auto& e : connections) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
            edge++;
        }
        if (edge < n - 1) return -1;
        vector<bool> visited(n, false);
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                count++;
                flood(visited, i, g);
            }
        }
        
        return count - 1;
    }
};