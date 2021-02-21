class Solution {
    struct ent_t {
       int x, y, d;   
    };
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        deque<ent_t> q;
        vector<vector<bool>> vis(rooms.size(), vector<bool>(rooms[0].size(), false));
        for (int x = 0; x < rooms.size(); ++x) {
            for (int y = 0; y < rooms[x].size(); ++y) {
                if (rooms[x][y] == 0) {
                    q.push_back(ent_t{x, y, 0});
                    vis[x][y] = true;
                }
            }
        }
        
        while (q.size()) {
            int sz = q.size();
            while (sz-->0) {
                auto top = q.front(); q.pop_front();
                for (int i = 0; i < 4; ++i) {
                   int nx = top.x + dx[i];
                    int ny = top.y + dy[i];
                    if (nx < 0 || nx >= rooms.size() || ny < 0 || ny >= rooms[0].size() || vis[nx][ny] || rooms[nx][ny] == -1) {
                        continue;
                    } 
                    vis[nx][ny] = true;
                    q.push_back(ent_t{nx, ny, top.d + 1});
                    rooms[nx][ny] = top.d + 1;
                }
            }
        }
    }
};