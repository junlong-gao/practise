class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        int R = 100;
        vector<vector<double>> c(R + 1, vector<double>(R + 1, 0));
        c[0][0] = poured;
        int i = 0;
        while (i < R) {
            for (int j = 0; j <= i; ++j) {
                if (c[i][j] > 1) {
                    double r = c[i][j] - 1;
                    c[i][j] = 1;
                    c[i + 1][j] += r / 2;
                    c[i + 1][j + 1] += r / 2;
                }
                if (i == query_row && j == query_glass) {
                    return c[query_row][query_glass];
                }
            }
            i++;
        }
        assert(0);
    }
};
