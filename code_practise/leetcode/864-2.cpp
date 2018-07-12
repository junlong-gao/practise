class Solution {
    vector<string> g;
    int n, m;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    int best = INT_MAX;
    int startX, startY;
    /*
    1. start point to end point
    2. keys obtained
        allowed nodes:
        1. . @
        2. keys obtained
        3. locks unlocked
    returns the shortest path
    */
    int shortestLength(
        int sx, int sy,
        char toFind,
        const vector<bool>& obtained
    ) {
        struct p {
            int x, y, d;
        };
        deque<p> q;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        
        // init
        q.emplace_back(p{sx, sy, 0});
        visited[sx][sy] = true;
        
        // search
        while(q.size()) {
            auto top = q.front(); q.pop_front();
            
            for (int i = 0; i < 4; i++) {
                int nx = top.x + dx[i];
                int ny = top.y + dy[i];
                
                if (nx < 0 || nx >= n) continue;
                if (ny < 0 || ny >= m) continue;
                if (visited[nx][ny]) continue;
                
                if (g[nx][ny] == '#') continue;
                if (g[nx][ny] >= 'A' && g[nx][ny] <= 'Z' && obtained[g[nx][ny] - 'A'] == 0) {
                    continue;
                }
                if (g[nx][ny] >= 'a' && g[nx][ny] <= 'z' && obtained[g[nx][ny] - 'a'] == 0) {
                    if (g[nx][ny] == toFind) {
                        return top.d + 1;
                    } else {
                        continue;
                    }
                }
                
                q.emplace_back(p{nx, ny, top.d + 1});
                visited[nx][ny] = true;
            }
        }
        
        return -1;
    }
    
    void solver(vector<pair<int, int>> &keysOrder) {
        vector<pair<int, int>> t{{2,0}, {0,4}, {2, 4}};
        int acc = 0;
        vector<bool> obtained(6, false);
        int cur = 0;
        int prevX = startX; int prevY = startY;
        for (auto & coor : keysOrder) {
            char toFind = g[coor.first][coor.second];
            int ret = shortestLength(prevX, prevY, toFind, obtained);

            if (ret == -1) return;
            
            acc += ret;
            obtained[toFind - 'a'] = true;
            cur++;
            prevX = coor.first; prevY = coor.second;
        }
        
        best = min(best, acc);
    }
    
    void gen(deque<pair<int, int>> &q, vector<pair<int, int>> &p) {
        if (q.empty()) { 
            solver(p);
        } else {
            for (int i = 0; i < q.size(); ++i) {
                p.push_back(q.front()); q.pop_front();
                gen(q, p);
                q.push_back(p.back()); p.pop_back();
            }
        }
    }
    
public:
    int shortestPathAllKeys(vector<string>& grid) {
        swap(g, grid);
        n = g.size();
        if (n == 0) return 0;
        m = g[0].size();
        //setup
        deque<pair<int, int>> keys;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (g[i][j] >= 'a' && g[i][j] <= 'z') {
                    keys.push_back({i, j});
                } else if (g[i][j] == '@') {
                    startX = i;
                    startY = j;
                }
            }
        }
        vector<pair<int, int>> p;
        //brute force
        gen(keys, p);
        
        return best == INT_MAX? -1 : best;
    }
};
