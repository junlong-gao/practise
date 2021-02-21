class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> c(graph.size(), -1);
        for (int i = 0; i < graph.size(); ++i) {
            if (c[i] != -1) continue;
            deque<int> q;
            q.push_back(i);
            c[i] = 1;
            while (q.size()) {
                auto top = q.front(); q.pop_front();
                for (auto n : graph[top]) {
                    if (c[n] == -1) {
                        c[n] = (c[top] + 1) % 2;
                        q.push_back(n);
                    } else {
                        if (c[n] == c[top]) return false;
                    }
                }
            }
        }
        
        return true;
    }
};
