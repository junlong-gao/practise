int x = [&]() {
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr);
    return 0;
}();

class Solution {
    struct UF {
        vector<int> p;
        vector<int> d;
        int n;
        vector<double> w;
        UF(int size):n(size) {
            for (int i = 0; i < n; ++i) {
                p.push_back(i);
            }
            d.resize(n, 0);
            w.resize(n, 1);
        }
        
        /*
        old:
        x--w1-> px -w2-> root
        
        new:
        x--w1 * w2--> root
                       ^
        px---w2--------|
        */
        int find(int x) {
            if (p[x] == x) return x;
            int px = p[x];
            p[x] = find(px);
            w[x] = w[x] * w[px];
            return p[x];
        }
        
        /*
        given x / y = w;
        link two trees;
        */
        bool link(int x, int y, double wi) {
            int px = find(x);
            int py = find(y);
            assert(w[px] == 1 && w[py] == 1);
            if (px == py) return false;
            if (d[px] > d[py]) {
                p[py] = px;
                // px / py = px / x * x / y;
                w[py] = w[x] * wi;
            } else {
                p[px] = py;
                w[px] = w[y] * 1 / wi; // XXX wi == 0?
                if (d[px] == d[py]) {
                    d[py]++;
                }
            }
            return true;
        }
    };
public:
    vector<double> calcEquation(
        vector<pair<string, string>> equations, 
        vector<double>&              values, 
        vector<pair<string, string>> queries)
    {
        // construct name -> id
        int counter = 0;
        unordered_map<string, int> id;
        for (auto & pr : equations) {
            if (id.count(pr.first) == 0) {
                id[pr.first] = counter++;
            }
            if (id.count(pr.second) == 0) {
                id[pr.second] = counter++;
            }
        }
        
        // use id to construct uf
        UF uf(counter);
        for (int i = 0; i < values.size(); ++i) {
            uf.link(id[equations[i].first], id[equations[i].second], values[i]);
        }
        
        // use uf to answer query
        vector<double> ret;
        for (auto & pr : queries) {
            string & p = pr.first;
            string & q = pr.second;
            if (id.count(p) == 0 || id.count(q) == 0) {
                ret.push_back(-1);
                continue;
            }
            
            int rp = uf.find(id.at(p));
            int rq = uf.find(id.at(q));
            if (rp != rq) {
                ret.push_back(-1);
            } else {
                ret.push_back(uf.w[id.at(q)] / uf.w[id.at(p)]);
            }
        }
        
        return ret;
    }
};