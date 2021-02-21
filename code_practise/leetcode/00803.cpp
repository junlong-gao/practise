class Solution {
    vector<vector<int>> g;
    vector<vector<bool>> visited;
    int n, m;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    vector<vector<bool>> mask;
    bool valid(int x, int y) {
        if (x < 0 || x >= n) return false;
        if (y < 0 || y >= m) return false;
        return true;
    }

    // flood the reachable region from x, y
    int searchNotFalling(int x, int y) {
        if (!valid(x, y) || g[x][y] != 1) return 0;
        int ret = 1;
        g[x][y] = 2;
        for (int i = 0; i < 4; ++i) {
            ret += searchNotFalling(x + dx[i], y + dy[i]);
        }
        return ret;
    }
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        swap(grid, g);
        n = g.size();
        if (n == 0) return {};
        m = g[0].size();
        visited = vector<vector<bool>>(n, vector<bool>(m, 0));

        vector<int> ret(hits.size(), 0);
        for (auto h : hits) {
            int x = h[0], y = h[1];
            if (g[x][y] == 0) g[x][y] = -1;
            else g[x][y] = 0;
        }

        // after removing all hit bricks, construct the final not falling region:
        for (int i = 0; i < m; ++i) {
            searchNotFalling(0, i);
        }

        // now we add all hit points back.
        // if adding it back will connect to the currently not falling region,
        // search from this point and expand the not falling region, and track the count
        // else we have a very special case that the hit point is at the top
        for (int i = hits.size() - 1; i >= 0; --i) {
            int x = hits[i][0];
            int y = hits[i][1];
            if (g[x][y] == -1) continue;
            g[x][y] = 1;
            // is this hit point connecting the not falling and the falling?
            // itself is by def not falling, but not counted.
            if (x == 0) {
                ret[i] += searchNotFalling(x, y) - 1;
            } else {
                for (int j = 0; j < 4; ++j) {
                    int nx = x + dx[j];
                    int ny = y + dy[j];
                    if (valid(nx, ny) && (g[nx][ny] == 2)) {
                       ret[i] += searchNotFalling(x, y) - 1;
                       break;
                    }
                }
            }
        }
        return ret;
    }
};
