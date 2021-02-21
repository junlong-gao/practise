class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        struct point {
          int r, c, v;
        };
        vector<point> Atable, Btable;
        if (A.empty() || A[0].empty() || B.empty() || B[0].empty()) return {};
        assert(A[0].size() == B.size());
        auto fill = [](vector<point>& t, vector<vector<int>>& m) {
            for (int i = 0; i < m.size(); ++i) {
                for (int j = 0; j < m[0].size(); ++j) {
                    if (m[i][j] != 0) {
                        t.push_back(point{i, j, m[i][j]});
                    }
                }
            }
        };

        fill(Atable, A); fill(Btable, B);
        vector<vector<int>> ret(A.size(), vector<int>(B[0].size(), 0));
        for (const auto &pa : Atable) {
            for (const auto &pb : Btable) {
                if (pa.c == pb.r) {
                    ret[pa.r][pb.c] += pa.v * pb.v;
                }
            }
        }
        return ret;
    }
};