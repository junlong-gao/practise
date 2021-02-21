class Solution {
    unordered_map<int, int> nodes;
    unordered_map<int, vector<int>> g;
    int s, d;
    bool search(int cur) {
        if (cur == d && g.count(cur) == 0) return true;
        if (g.count(cur) == 0) return false;
        for (auto n : g[cur]) {
            //cout << n << endl;
            if (nodes[n] == 1) return false;
            if (nodes[n] == 2) continue;
            nodes[n] = 1;
            if (!search(n)) return false;
            nodes[n] = 2;
        }
        return true;
    }
public:
    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
        }
        s = source;
        d = destination;
        nodes[s] = 1;
        return search(s);
    }
};
