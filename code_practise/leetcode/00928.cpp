/*
*/
class Solution {
    void search(int i, vector<vector<int>> &g, vector<bool> &vt, unordered_set<int> &m, vector<int> *output) {
        //cout << i << endl;
        if (m.count(i) > 0) {
            output->push_back(i);
            return;
        }
        if (output->size() > 1) {
            return;
        }
        for (int j = 0; j < g.size(); ++j) {
            if (g[i][j] == 0) continue;
            if (vt[j]) continue;
            vt[j] = true;
            search(j, g, vt, m, output);
        }
    }
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
       unordered_map<int, int> affected;
       unordered_set<int> m;
       for (int i = 0; i < initial.size(); ++i) {
           m.insert(initial[i]);
       }

       for (int i = 0; i < graph.size(); ++i) {
           if (m.count(i)) continue;
           vector<bool> vt(graph.size(), false);
           vt[i] = true;
           vector<int> tmp;
           search(i, graph, vt, m, &tmp);
           if (tmp.size() > 1 || tmp.empty()) {
               continue;
           }
           affected[tmp.back()]++; 
       }

       int best = -1;
       int ret = 0;
       sort(initial.begin(), initial.end());
       for (auto n : initial) {
           if (affected[n] > best) {
               ret = n;
               best = affected[n];
           }
       }

       return ret;
    }
};
