class Solution {
    struct uf_t {
        vector<int> p, d;
        int tot;
        uf_t(int n) {
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
    int countComponents(int n, vector<vector<int>>& edges) {
        uf_t uf(n);
        for (auto &e : edges) {
            uf.link(e[0], e[1]);
        }

        return uf.tot;
    }
};