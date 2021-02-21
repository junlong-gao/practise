class Solution {
    struct heap_node {
        int u, d;
        bool operator<(const heap_node& other) const {
            return d > other.d;
        }
    };
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        const int infty = INT_MAX/2;
        
        priority_queue<heap_node> q; q.push(heap_node{K, 0});
        
        vector<int> d(N + 1, infty); d[K] = 0;
        
        unordered_map<int, unordered_map<int, int>> w;
        unordered_map<int, vector<int>> edges;
        for (const auto& edge : times) {
            w[edge[0]][edge[1]] = edge[2];
            edges[edge[0]].push_back(edge[1]);
        }
        
        int ret = 0;
        int count = 0;
        while(q.size()) {
            auto t = q.top(); q.pop();
            if (t.d != d[t.u]) {
                assert(t.d > d[t.u]);
                continue;
            }
            ret = max(t.d, ret);
            count++;
            
            int u = t.u;
            for (const auto& v : edges[u]) {
                if (w[u].count(v) && d[v] > d[u] + w[u][v]) {
                    d[v] = d[u] + w[u][v];
                    q.push(heap_node{v, d[v]});
                }
            }
        }
        
        return count == N ? ret : -1;
    }
};
