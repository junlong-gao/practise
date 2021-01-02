class Solution {
    int search(int token, int i, vector<vector<int>> &g, vector<bool> &vt, unordered_map<int, vector<int>> &tokens, unordered_set<int> &m) {
        int ret = 1;
        if (m.count(i)) {
            tokens[token].push_back(i);
        }

        for (int j = 0; j < g.size(); ++j) {
            if (g[i][j] == 0) continue;
            if (vt[j]) continue;
            vt[j] = true;
            ret += search(token, j, g, vt, tokens, m);
        }

        return ret;
    }
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        vector<bool> vt(graph.size(), false);
        unordered_set<int> m;
        unordered_map<int, vector<int>> tokens;
        map<int, vector<int>> countM;
        for (auto e : initial) {
            m.insert(e);
        }

        int token = 1;
        for (int i = 0; i < graph.size(); ++i) {
            if (vt[i]) continue;
            vt[i] = true;
            int count = search(token, i, graph, vt, tokens, m);
            if (tokens[token].size() == 1) {
                countM[count].push_back(tokens[token].back());
            }
            token++;
        }

        for (auto it = countM.rbegin(); it != countM.rend(); ++it) {
            sort(it->second.begin(), it->second.end());
            return it->second.front();
        }

        sort(initial.begin(), initial.end());
        return initial.front();
    }
};
