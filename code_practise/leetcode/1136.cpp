class Solution {
public:
    int minimumSemesters(int N, vector<vector<int>>& relations) {
        vector<vector<int>> g(N + 1);
        vector<int> ins(N + 1);
        deque<int> q;
        for (auto& e : relations) {
            g[e[0]].push_back(e[1]);
            ins[e[1]]++;
        }
        
        int taken = 0;
        int ret = 0;
        for (int i = 1; i <= N; ++i) {
            if (ins[i] == 0) {
                q.push_back(i);
                taken++;
            }
        }
        
        while(q.size()) {
            int s = q.size();
            ret++;
            for (int i = 0; i < s; ++i) {
                for (auto u : g[q.front()]) {
                    ins[u]--;
                    if (ins[u] == 0) {
                        q.push_back(u);
                        taken++;
                    }
                }
                q.pop_front();
            }
        }
        return taken == N ? ret : -1;
    }
};
