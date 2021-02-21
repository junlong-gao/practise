class Solution {
    struct ent {
        int x, y;
    };
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
       vector<vector<bool>> vis(maze.size(), vector<bool>(maze[0].size(), false));
        deque<ent> q{ent{start[0], start[1]}};

        vis[start[0]][start[1]] = true;

        while (q.size()) {
            auto top = q.front(); q.pop_front();
            if (top.x == destination[0] && top.y == destination[1]) {
                return true;
            }
            for (int i = 0; i < 4; ++i) {
                int nx = top.x; int ny = top.y;
                while (true) {
                    int nnx = nx + dx[i]; int nny = ny + dy[i];
                    if (nnx < 0 || nnx >= maze.size() || nny < 0 || nny >= maze[0].size() || maze[nnx][nny] == 1) {
                        break;
                    }
                    nx = nnx; ny = nny;
                }
                if (vis[nx][ny]) continue;
                vis[nx][ny] = true;
                q.push_back(ent{nx, ny});
            }
        }

        return false;
    }
};