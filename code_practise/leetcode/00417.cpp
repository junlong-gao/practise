class Solution {
    struct ent_t {
        int x, y;
    };
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    void search(bool isPacific, vector<vector<int>>& g, vector<vector<int>> &state) {
        vector<vector<bool>> vis(g.size(), vector<bool>(g[0].size(), false));
        deque<ent_t> q;
        if (isPacific) {
            for (int x = 0; x < g.size(); ++x) {
                vis[x][0] = true;
                q.push_back(ent_t{x, 0});
                state[x][0]++;
            }
            for (int y = 1; y < g[0].size(); ++y) {
                vis[0][y] = true;
                q.push_back(ent_t{0, y});
                state[0][y]++;
            }
        } else {
            for (int x = 0; x < g.size() - 1; ++x) {
                int fy = g[0].size() - 1; 
                vis[x][fy] = true;
                q.push_back(ent_t{x, fy});
                state[x][fy]++;
            }
            for (int y = 0; y < g[0].size(); ++y) {
                int fx = g.size() - 1;
                vis[fx][y] = true;
                q.push_back(ent_t{fx, y});
                state[fx][y]++;
            }
        }
        
        while (q.size()) {
            auto top = q.front(); q.pop_front();
            for (int i = 0; i < 4; ++i) {
                int nx = top.x + dx[i];
                int ny = top.y + dy[i];
                if (nx < 0 || nx >= g.size() || ny < 0 || ny >= g[0].size() || vis[nx][ny] || g[nx][ny] < g[top.x][top.y]){
                    continue;
                }
                vis[nx][ny] = true;
                q.push_back(ent_t{nx, ny});
                state[nx][ny]++;
            }
        }
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        if (matrix.size() == 0) return {};
        
        vector<vector<int>> state(matrix.size(), vector<int>(matrix[0].size(), 0));
        search(true, matrix, state);
        search(false, matrix, state);
        
        vector<vector<int>> ret;
        for (int x = 0; x < matrix.size(); ++x) {
            for (int y = 0; y < matrix[x].size(); ++y) {
                if (state[x][y] == 2) {
                    ret.push_back({x, y});
                }
            }
        }
        
        return ret;
    }
};