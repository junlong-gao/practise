class Solution {
    unordered_map<string,
       unordered_map<string, double>> g;
    unordered_map<string, bool> visited;

    bool search(
       double &sofar,
       string cur,
       string dst) {
       if (cur == dst) return true;

       for (auto &nextPr : g[cur]) {
           string next = nextPr.first;
           double w = nextPr.second;

           if (visited[next]) continue;

           visited[next] = true;
           sofar *= w;
           if (search(sofar, next, dst)) {
               return true;
           }

           sofar /= w;
           visited[next] = false;
       }

       return false;
    }
public:
    vector<double> calcEquation(
        vector<vector<string>>& equations,
        vector<double>& values,
        vector<vector<string>>& queries) {
        for (int i = 0; i < equations.size(); ++i) {
            g[equations[i][0]][equations[i][1]] = values[i];
            g[equations[i][1]][equations[i][0]] = 1.0 / values[i];
        }

        vector<double> ret;
        for (auto &q : queries) {
            visited = unordered_map<string, bool>();
            for (auto & nPr : g) {
                visited[nPr.first] = false;
            }
            visited[q[0]] = true;
            double ans = 1;
            if (g.count(q[0]) && search(ans, q[0], q[1])) {
                ret.push_back(ans);
            } else {
                ret.push_back(-1);
            }
        }

        return ret;
    }
};
