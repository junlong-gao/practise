class Solution {
    struct uf_t {
        vector<int> p;
        uf_t(int n) {
            for (int i = 0; i < n; ++i) {
                p.push_back(i);
            }
        }
        int find(int x) {
            if (p[x] == x) {
                return p[x];
            } else {
                int px = find(p[x]);
                p[x] = px;
                return px;
            }
        }
        void link(int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px == py) {
                return;
            }
            p[px] = py;
        }
    };
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        uf_t uf(s.size());
        for (auto pr : pairs) {
            uf.link(pr[0], pr[1]);
        }
        unordered_map<int, vector<int>> groups;
        for (int i = 0; i < s.size(); ++i) {
            groups[uf.find(i)].push_back(i);
        }

        for (auto &pr : groups) {
            vector<int> &idxs = pr.second;
            std::sort(idxs.begin(), idxs.end());

            string tmp;
            for (auto idx : idxs) {
                tmp.push_back(s[idx]);
            }
            std::sort(tmp.begin(), tmp.end());

            for (int i = 0; i < idxs.size(); ++i) {
                s[idxs[i]] = tmp[i];
            }
        }

        return s;
    }
};