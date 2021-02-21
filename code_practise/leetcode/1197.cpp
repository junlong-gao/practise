class Solution {
    struct ent_t {
        int x, y;
    };
    int dx[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
    int dy[8] = {-2, -1, 1, 2, -2, -1, 1, 2};
    
public:
    int minKnightMoves(int x, int y) {
        unordered_map<int, unordered_map<int, int>> vis;
        deque<ent_t> q;
        
        vis[0][0] = 1;
        q.push_back(ent_t{0, 0});
        int d = 0;
        x = abs(x); y = abs(y);
        while (q.size()) {
            int sz = q.size();
            while(sz-->0) {
                auto top = q.front();
                q.pop_front();
                if (top.x == x && top.y == y) {
                    return d;
                }
                for (int i = 0; i < 8; ++i) {
                    int nx = abs(top.x + dx[i]);
                    int ny = abs(top.y + dy[i]);
                    if (nx > 300 || ny > 300 || vis[nx][ny] == 0) {
                        vis[nx][ny] = 1;
                        q.push_back(ent_t{nx, ny});
                    }
                }
            }
            d++;
        }
        return 0;
    }