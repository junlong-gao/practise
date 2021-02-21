class Solution {
    struct pt {
        int x, y, r;
    };
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        if (n == 0) return 0;
        
        int m = grid[0].size();
        
        vector<vector<vector<bool>>> visited(
        n, vector<vector<bool>>(m, vector<bool>(k + 1, false)));
        
        visited[0][0][k] = true;
        deque<pt> q; q.push_back(pt{0, 0, k});
        
        int ret = 0;
        while (q.size()) {
            int sz = q.size();
            for (int i = 0; i < sz; ++i) {
                auto top = q.front(); q.pop_front();
                if (top.x == n - 1 && top.y == m - 1) {
                    return ret;
                }
                //cout << top.x << " " << top.y << endl;
                for (int j = 0; j < 4; ++j) {
                    int nx = top.x + dx[j];
                    int ny = top.y + dy[j];
                    int nr = top.r + (grid[top.x][top.y] == 1 ? -1 : 0);
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m || nr < 0 || visited[nx][ny][nr]) {
                        continue;
                    }
                    q.push_back(pt{nx, ny, nr});
                    visited[nx][ny][nr] = true;
                }
            }
            ret++;
        }
        return -1;
    }
};
