class Solution {
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    vector<vector<int>> dp;
    vector<vector<int>> g;
    bool isValid(int x, int y) {
        if (x < 0 || x >= g.size()) {
            return false;
        }
        if (y < 0 || y >= g[0].size()) {
            return false;
        }
        return true;
    }
    int dfs(int x, int y) {
        if (dp[x][y] != 0) {
            return dp[x][y];
        }
        int &ret = dp[x][y];
        ret = 1;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny) && g[nx][ny] > g[x][y]) {
                ret = max(1 + dfs(nx, ny), ret);
            }
        }
        return ret;
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        swap(g, matrix);
        dp = g;
        for (int i = 0; i < g.size(); ++i) {
            for (int j = 0; j < g[i].size(); ++j) {
                dp[i][j] = 0;
            }
        }
        int ret = 0;
        for (int i = 0; i < g.size(); ++i) {
            for (int j = 0; j < g[i].size(); ++j) {
                ret = max(ret, dfs(i, j));
            }
        }
        return ret;
    }
};