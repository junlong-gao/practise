class Solution {
    struct ent_t {
        string n;
        double d;
    };
    double search(unordered_map<string, unordered_map<string, double>> &g, string &src, string &dst) {
        deque<ent_t> q{ent_t{src, 1.0}};
        unordered_set<string> vis;
        vis.insert(src);
        while (q.size()) {
            int n = q.size();
            while (n-->0) {
                auto top = q.front();
                q.pop_front();
                if (top.n == dst) {
                    return top.d;
                }
                for (auto n : g[top.n]) {
                    if (vis.count(n.first)) {
                        continue;
                    }
                    vis.insert(n.first);
                    q.push_back(ent_t{n.first, top.d * n.second});
                }
            }
        }
        return -1;
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, unordered_map<string, double>> g;
        for (int i = 0; i < equations.size(); ++i) {
            g[equations[i][0]][equations[i][1]] = values[i];
            g[equations[i][1]][equations[i][0]] = 1.0 / values[i];
        }
        
        vector<double> ret;
        for (auto & qry : queries) {
           if (g.count(qry[0]) * g.count(qry[1]) == 0) {
               ret.push_back(-1);
           } else {
               ret.push_back(search(g, qry[0], qry[1])); 
           }
        }
        return ret;
    }
};
