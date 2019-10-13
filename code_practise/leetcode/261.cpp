class Solution {
    struct UF {
        vector<int> p, d;
        UF(int n) {
            for (int i = 0; i < n; ++i) { p.push_back(i); }
            d.resize(n, 0);
        }
        int Find(int x) {
            if (p[x] != x) {  return p[x] = Find(p[x]); }
            return x;
        }
        bool IsSame (int x, int y) {
            return Find(x) == Find(y);
        }
        void Union(int x, int y) {
            if (IsSame(x, y)) { return; }
            
            int px = Find(x); int py = Find(y);
            
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
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false;
        UF uf(n);
        for (const auto& e : edges) {
            int x = e[0]; int y = e[1];
            if (uf.IsSame(x, y)) { return false; }
            uf.Union(x, y);
        }
        return true;
    }
};
