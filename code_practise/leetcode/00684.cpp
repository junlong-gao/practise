class Solution {
    struct UF {
        vector<int> d, p;
        UF(int size) {
            d.resize(size, 0);
            for (int i = 0; i < size; ++i) {
                p.push_back(i);
            }
        }
        
        int find(int x) {
            if (p[x] == x) return x;
            else return p[x] = find(p[x]);
        }
        
        bool link(int x, int y) {
            int px = find(x), py = find(y);
            if (px == py) return false;
            
            if (d[px] > d[py]) {
                p[py] = px;
            } else {
                p[px] = py;
                if (d[px] == d[py]) {
                    d[py]++;
                }
            }
            return true;
        }
    };
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        UF uf(n);
        for (const vector<int> & e : edges) {
            if (!uf.link(e[0] - 1, e[1] - 1)) {
                return e;
            }
        }
        assert(0);
    }
};