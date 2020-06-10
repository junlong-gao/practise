class Solution {
    struct P {
        int x; int y;
    };
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    int invI[4] = {2, 3, 0, 1};
    
    bool canReach(vector<vector<char>>& grid, P cur, P e) {
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        visited[cur.x][cur.y] = true;
        return _canReach(grid, visited, cur, e);
    }
    bool _canReach(vector<vector<char>>& grid, vector<vector<bool>>& visited,
                  P cur, P e) {
        if (cur.x == e.x && cur.y == e.y) return true;
        for (int i = 0; i < 4; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size()
                || visited[nx][ny] || grid[nx][ny] != '.') {
                continue;
            }
            visited[nx][ny] = true;
            if (_canReach(grid, visited, P{nx, ny}, e)) {
                return true;
            }
        }
        return false;
    }
public:
    int minPushBox(vector<vector<char>>& grid) {
        P s, t, p;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == 'B') {
                    s = P{i, j};
                    grid[i][j] = '.';
                } else if (grid[i][j] == 'T') {
                    t = P{i, j};
                    grid[i][j] = '.';
                } else if (grid[i][j] == 'S') {
                    p = P{i, j};
                    grid[i][j] = '.';
                }
            }
        }
        bool visited[21][21][21][21];
        for (int i = 0; i < 21; ++i) {
            for (int j = 0; j < 21; ++j) {
                for (int k = 0; k < 21; ++k) {
                    for (int l = 0; l < 21; ++l) {
                        visited[i][j][k][l] = false;
                    }
                }
            }
        }
        
        visited[s.x][s.y][p.x][p.y] = true;
        deque<pair<P, P>> q{make_pair(s, p)};
        int ret = 0;
        while (q.size()) {
            int sz = q.size();
            for (int i = 0; i < sz; ++i) {
                auto f = q.front(); q.pop_front();
                if (f.first.x == t.x && f.first.y == t.y) {
                    return ret;
                }
                for (int i = 0; i < 4; ++i) {
                    int nbx = f.first.x + dx[i];
                    int nby = f.first.y + dy[i];
                    int npx = f.first.x + dx[invI[i]];
                    int npy = f.first.y + dy[invI[i]];
                    assert(npx + dx[i] == f.first.x);
                    assert(npy + dy[i] == f.first.y);
                    if (nbx < 0 || nbx >= grid.size() || nby < 0 || nby >= grid[0].size() ||
                        grid[nbx][nby] != '.') {
                        continue;
                    }
                    if (npx < 0 || npx >= grid.size() || npy < 0 || npy >= grid[0].size() ||
                        grid[npx][npy] != '.') {
                        continue;
                    }
                    if (visited[nbx][nby][npx][npy]) {
                        continue;
                    }
                    grid[f.first.x][f.first.y] = 'B';
                    if (!canReach(grid, P{f.second.x, f.second.y}, P{npx, npy})) {
                        grid[f.first.x][f.first.y] = '.';
                        continue;
                    }

                    grid[f.first.x][f.first.y] = '.';
                    visited[nbx][nby][npx][npy] = true;

                    q.push_back(make_pair(P{nbx, nby}, P{f.first.x, f.first.y}));
                }
            }
            ret++;
        }
        
        return -1;
    }
};
