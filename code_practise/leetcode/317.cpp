class Solution {
    /*
    -1 : building
    -2 : wall

    for each cell compute distance sum to all building, one building
    at a time. if see int_max, means this cell cannot be reached by
    this building
    */
public:
    using g_t = vector<vector<int>>;
    using b_t = vector<vector<bool>>;
    struct ent_t {
        int x, y;
    };
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    void addOneBuildingDistance(int bx, int by, g_t &grid) {
        g_t tmp(grid.size(), vector<int>(grid[0].size(), 0));
        b_t vis(grid.size(), vector<bool>(grid[0].size(), false));

        deque<ent_t> q{ent_t{bx, by}};
        vis[bx][by] = true;
        int d = 0;
        while (q.size()) {
            int sz = q.size();
            d++;
            while (sz-->0) {
                auto top = q.front(); q.pop_front();
                for (int i = 0; i < 4; ++i) {
                    int nx = top.x + dx[i];
                    int ny = top.y + dy[i];
                    if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size() || vis[nx][ny] || grid[nx][ny] < 0) {
                        continue;
                    }
                    vis[nx][ny] = true;
                    tmp[nx][ny] = d;
                    q.push_back(ent_t{nx, ny});
                }
            }
        }

        for (int x = 0; x < grid.size(); ++x) {
            for (int y = 0; y < grid[x].size(); ++y) {
                if (grid[x][y] < 0) continue;
                if (tmp[x][y] == 0 || grid[x][y] == INT_MAX) {
                    grid[x][y] = INT_MAX;
                } else {
                    grid[x][y] += tmp[x][y];
                }
            }
        }
    }

    int shortestDistance(vector<vector<int>>& grid) {
        for (int x = 0; x < grid.size(); ++x) {
            for (int y = 0; y < grid[x].size(); ++y) {
                if (grid[x][y]) {grid[x][y] = -grid[x][y];}
            }
        }
        for (int x = 0; x < grid.size(); ++x) {
            for (int y = 0; y < grid[x].size(); ++y) {
                if (grid[x][y] == -1) {
                    addOneBuildingDistance(x, y, grid);
                }
            }
        }

        int best = INT_MAX;
        for (int x = 0; x < grid.size(); ++x) {
            for (int y = 0; y < grid[x].size(); ++y) {
                if (grid[x][y] > 0 && grid[x][y] < best) {
                    best = grid[x][y];
                }
            }
        }

        if (best == INT_MAX) {
            return -1;
        }
        return best;
    }
};