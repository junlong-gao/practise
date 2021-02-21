class Solution {
    struct p {
        int n;
        int d;
        double pb;
    };
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        unordered_map<int, vector<int>> g;
        for (auto &e : edges) {
            g[min(e[0], e[1])].push_back(max(e[0], e[1]));
        }

        deque<p> q {p{1, 0, 1}};

        while (q.size()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                auto top = q.front();
                q.pop_front();
                for (auto v : g[top.n]) {
                  double pb = g[top.n].size();
                  q.push_back(p{v, top.d + 1, top.pb / pb});
                }
                if (top.n == target &&
                    (top.d == t || top.d < t && g[top.n].size() == 0)) {
                  return top.pb;
                }
            }
        }
        return 0;
    }
};
