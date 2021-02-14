class Solution {
    struct ent_t {
        int x, y, d;
    };
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    int search(const vector<string> &grid, set<char> &keys, int sx, int sy, char target, int *ex, int *ey) {
        vector<vector<bool>> vis(grid.size(), vector<bool>(grid[0].size(), false));
        deque<ent_t> q{ent_t{sx, sy, 0}};
        vis[sx][sy] = true;
        while (q.size()) {
            int sz = q.size();
            while (sz-->0) {
                auto top = q.front(); q.pop_front();
                for (int i = 0; i < 4; ++i) {
                    int nx = top.x + dx[i];
                    int ny = top.y + dy[i];
                    if (nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size() ||
                        vis[nx][ny] || 
                        grid[nx][ny] == '#' || 
                        (isupper(grid[nx][ny]) && keys.count(tolower(grid[nx][ny])) == 0) ||
                        (islower(grid[nx][ny]) && keys.count(grid[nx][ny]) == 0 && grid[nx][ny] != target)) {
                        continue;
                    }
                    
                    vis[nx][ny] = true;
                    if (grid[nx][ny] == target) {
                        *ex = nx;
                        *ey = ny;
                        return top.d + 1;
                    } else {
                        q.push_back(ent_t{nx, ny, top.d + 1});
                    }
                }
            }
        }
        
        return -1;
    }
    
    int reach(const vector<string> &grid, const string & order, int sx, int sy) {
       set<char> keys;
        int ret = 0;
        for (int i = 0; i < order.size(); ++i) {
            int step = search(grid, keys, sx, sy, order[i], &sx, &sy);
            if (step == -1) {
                return -1;
            }
            ret += step;
            keys.insert(order[i]);
        }
        
        return ret;
    }
    
    void genSearch(const vector<string> &g, int sx, int sy, deque<char> &remain, string &pfx, int &ret) {
        if (remain.empty()) {
            int sol = reach(g, pfx, sx, sy);
            if (sol != -1) {
                ret = min(ret, sol);
            }
        } else {
            int sz = remain.size();
            while (sz-->0) {
                pfx.push_back(remain.front()); remain.pop_front();
                
                genSearch(g, sx, sy, remain, pfx, ret);
                
                remain.push_back(pfx.back()); pfx.pop_back();
            }
        }
    }
public:
    int shortestPathAllKeys(vector<string>& grid) {
        deque<char> keys;
        int sx, sy;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (islower(grid[i][j])) {
                    keys.push_back(grid[i][j]);
                }
                if (grid[i][j] == '@') {
                    sx = i; sy = j;
                }
            }
        }
        
        string order;
        int ret = INT_MAX;
        genSearch(grid, sx, sy, keys, order, ret);
        
        if (ret == INT_MAX) {
            return -1;
        }
        return ret;
    }
};