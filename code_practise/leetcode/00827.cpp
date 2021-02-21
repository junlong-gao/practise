class Solution {
    int dx[4] = {1, 0, -1 , 0};
    int dy[4] = {0, 1, 0 , -1};
    struct ent {
        int x; int y;
    };
    int search(vector<vector<int>>& grid, vector<vector<bool>> &vis, int x, int y, int id) {
        assert(grid[x][y] == 1);
        deque<ent> q{ent{x, y}};

        vis[x][y] = true;
        grid[x][y] = id;
        int ret = 1;

        while (q.size()) {
            int sz = q.size();
            while(sz-->0) {
                auto top = q.front(); q.pop_front();
                for (int i = 0; i < 4; ++i) {
                    int nx = top.x + dx[i];
                    int ny = top.y + dy[i];
                    if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size() || vis[nx][ny] ||
                       grid[nx][ny] != 1) {
                        continue;
                    }

                    vis[nx][ny] = true;
                    grid[nx][ny] = id;
                    q.push_back(ent{nx, ny});
                    ret++;
                }
            }
        }
        return ret;
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        unordered_map<int, int> szs;
        int id = 2;
        vector<vector<bool>> vis(grid.size(), vector<bool>(grid[0].size(), false));
        int best = 0;

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == 1) {
                    int oldId = id++;
                    szs[oldId] = search(grid, vis, i, j, oldId);
                    best = max(best,szs[oldId]); // consider the case of not changing at all
                }
            }
        }

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == 0) {
                    set<int> used;
                    int total = 1;
                    for (int k = 0; k < 4; ++k) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size() ||
                            used.count(grid[nx][ny])) {
                            continue;
                        }
                        total += szs[grid[nx][ny]];
                        used.insert(grid[nx][ny]);
                    }
                    best = max(total, best);
                }
            }
        }
        return best;
    }
};