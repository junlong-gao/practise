class Solution {
    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
    vector<vector<vector<double>>> dp
    {26, vector<vector<double>>(26, vector<double>(101, -1))};
public:
    double knightProbability(int N, int K, int r, int c) {

        if (r < 0 || r >= N || c < 0 || c >= N) {
            return 0;
        }
        if (K <= 0) {
            return 1;
        }
        double &ret = dp[r][c][K];
        if (ret >= 0) {
            return ret;
        }
        ret = 0;
        for (int i = 0; i < 8; ++i) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            ret += knightProbability(N, K - 1, nr, nc) / 8.0;
        }

        return ret;
    }
};
