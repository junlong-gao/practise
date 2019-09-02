class Solution {
    struct UF {
        vector<int> p, d;
        UF(int n) {
            for (int i = 0; i < n; ++i) {
                d.push_back(0); p.push_back(i);
            }
        }
        
        int find(int x) {
            if (p[x] != x) {
                return p[x] = find(p[x]);
            }
            return p[x];
        }
        
        void uni(int x, int y) {
            int px = find(x); int py = find(y);
            if (px == py) return;
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
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        unordered_map<string, int> owner;
        UF uf(n);
        for (int i = 0; i < accounts.size(); ++i) {
            for (int j  = 1; j < accounts[i].size(); ++j) {
                if (owner.count(accounts[i][j]) == 0) {
                    owner[accounts[i][j]] = i;
                } else {
                    uf.uni(i, owner[accounts[i][j]]);
                }
            }
        }
        
        unordered_map<int, vector<string>> merge_ret;
        for (auto & pr : owner) {
            merge_ret[uf.find(pr.second)].push_back(pr.first);
        }
            
        vector<vector<string>> ret;
        for (auto & pr : merge_ret) {
            ret.push_back({accounts[pr.first].front()});
            ret.back().insert(ret.back().begin() + 1, pr.second.begin(), pr.second.end());
            sort(ret.back().begin() + 1, ret.back().end());
        }
        return ret;
    }
};
