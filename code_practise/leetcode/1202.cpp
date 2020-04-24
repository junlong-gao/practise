class Solution {
    struct UF {
        vector<int> p, d;
        UF(int n) {
            for (int i = 0; i < n; ++i) {
                p.push_back(i);
                d.push_back(0);
            }
        }
        int find(int x) {
            if (p[x] == x) {
                return x;
            }
            return p[x] = find(p[x]);
        }
        void link(int x, int y) {
            int px = find(x);
            int py = find(y);
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
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        UF uf(s.length());
        for (auto pr : pairs) {
            uf.link(pr[0], pr[1]);
        }
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < s.length(); ++i) {
            mp[uf.find(i)].push_back(i);
        }
        for (auto &pr : mp) {
            sort(pr.second.begin(), pr.second.end());
            string tmp;
            for (int i = 0; i < pr.second.size(); ++i) {
                tmp.push_back(s[pr.second[i]]);
            }
            sort(tmp.begin(), tmp.end());
            for (int i = 0; i < pr.second.size(); ++i) {
                s[pr.second[i]] = tmp[i];
            }
        }
        return s;
    }
};