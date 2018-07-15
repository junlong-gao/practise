static int x = []() { std::ios::sync_with_stdio(false); cin.tie(NULL); return 0; }();
class Solution {
    // HA is a structure to dynamically build a forest and query the highest parent of each node.
    struct HA {
        vector<int> p;
        HA(int size) : p(size) {
            iota(p.begin(), p.end(), 0);
        }

        int find(int x) {
           if (p[x] == x) return x;
           return p[x] = find(p[x]);
        }
        
        // if x is a subtree root and is not y's subtree root,
        // (so x is a proper subtree of y)
        // set x's parent to be y and return true
        // otherwise return false;
        bool setParent(int x, int y) {
           if (p[x] != x || x == find(y)) return false;
           p[x] = y;
           return true;
        }
    };
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int N = edges.size();
        vector<int> deleted, undeleted;
        vector<int> p(N + 1, 0);
        HA ha(N + 1);
        
        // first try to find a 2de edge to delete
        for (auto & e : edges) {
            if (p[e[1]] != 0) {
               deleted = e;
               undeleted = vector<int>{p[e[1]], e[1]};
               e[1] = 0; // delete this edge by grounding it
               break;
            } else {
               p[e[1]] = e[0];
            }
        }
        // now that there is no 2de edge, every setParent should
        // succeed
        for (const auto & e : edges) {
            if (!ha.setParent(e[1], e[0])) {
               if (deleted.empty()) return e;
               else return undeleted;
            }
        }

        assert(deleted.size() == 2);
        return deleted;
    }
};
