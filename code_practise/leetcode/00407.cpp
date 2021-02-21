class Solution {
    struct ent_t {
        int x; int y; int h;
    };
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        auto cmp = [](const ent_t &l, const ent_t &r) {
            return l.h > r.h;
        };
       priority_queue<ent_t, vector<ent_t>, decltype(cmp)> q(cmp);
        vector<vector<bool>> vis(heightMap.size(), vector<bool>(heightMap[0].size(), false));
        for (int y = 0; y < heightMap[0].size() - 1; ++y) {
            q.push(ent_t{0, y, heightMap[0][y]});
            vis[0][y] = true;
        }
        for (int x = 0; x < heightMap.size(); ++x) {
            int fy = heightMap[0].size() - 1;
            q.push(ent_t{x, fy, heightMap[x][fy]});
            vis[x][fy] = true;
        }
        for (int y = heightMap[0].size() - 1; y >= 0; --y) {
            int fx = heightMap.size() - 1;
            q.push(ent_t{fx, y, heightMap[fx][y]});
            vis[fx][y] = true;
        }
        for (int x = heightMap.size() - 1; x >= 0; --x) {
            q.push(ent_t{x, 0, heightMap[x][0]});
            vis[x][0] = true;
        }
        
        int ret = 0;
        while(q.size()) {
            auto top = q.top(); q.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = top.x + dx[i];
                int ny = top.y + dy[i];
                if (nx < 0 || nx >= heightMap.size() || ny < 0 || ny >= heightMap[0].size() || vis[nx][ny]) {
                    continue;
                }
                ret += max(0, top.h - heightMap[nx][ny]);
                // fill water on nx ny...
                q.push(ent_t{nx, ny, max(heightMap[nx][ny], top.h)});
                vis[nx][ny] = true;
            }
        }
        
        return ret;
    }
};