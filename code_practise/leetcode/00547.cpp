class Solution {
    struct uf_t {
        vector<int> p, d;
        int tot;
        uf_t (int n) {
            for (int i = 0; i < n; ++i) {
                p.push_back(i);
                d.push_back(0);
            }
            tot = n;
        }
        int find(int x) {
            if (p[x] == x) {
                return x;
            }
            int ret = find(p[x]);
            p[x] = ret;
            return ret;
        }
        int size() {
            return tot;
        }
        void link(int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px == py) {
                return;
            }
            tot--;
            if (d[px] > d[py]) {
                p[py] = px;
            } else {
                p[px] = py;
                if (d[px] == d[py]) {
                    d[py]++;
                }
            }
        }
    };
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        uf_t uf(isConnected.size());
        for (int i = 0; i < isConnected.size(); ++i) {
            for (int j = 0; j < isConnected[i].size(); ++j) {
                if (isConnected[i][j]) {
                    uf.link(i, j);
                }
            }
        }
        return uf.size();
    }
};