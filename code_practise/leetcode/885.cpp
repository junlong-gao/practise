class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        int dy[4] = {1, 0, -1, 0};
        int dx[4] = {0, 1, 0, -1};
        vector<vector<int>> ret {{r0, c0}};
        for (int i = 1; ; i += 2) {
            for (int j = 0; j < 4; ++j) {
                int d = i + j / 2;
                for (int k = 0; k < d; ++k) {
                    r0 += dx[j];
                    c0 += dy[j];
                    if (r0 >= 0 && r0 < R && c0 >= 0 && c0 < C) {
                        ret.push_back({r0, c0});
                    }
                    if (ret.size() == R*C) {
                        return ret;
                    }
                }
            }
        }
    }
};
