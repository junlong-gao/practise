class Solution {
    int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
    
    struct ent_t {
        int x;
        int y;
        int d;
    };
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if (grid.empty()) {
            return 0;
        }
        int n = grid.size(); int m = grid[0].size();
        vector<vector<bool>> vis(grid.size(), vector<bool>(grid[0].size(), false));
        if (grid[0][0]) {
            return -1;
        }
        deque<ent_t> q{ent_t{0, 0, 1}};
        vis[0][0] = true;
        
        while (q.size()) {
            int s = q.size();
            while (s-->0) {
                auto top = q.front();
                q.pop_front();
                if (top.x == n - 1 && top.y == m - 1) {
                    return top.d;
                }
                for (int i = 0; i < 8; ++i) {
                    int nx = top.x + dx[i];
                    int ny = top.y + dy[i];
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m || vis[nx][ny] || grid[nx][ny] != 0) {
                        continue;
                    }
                    q.push_back(ent_t{nx, ny, top.d + 1});
                    vis[nx][ny] = true;
                }
            }
        }
        return -1;
    }
};
