class Solution {
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        const int n = maze.size(); if (n == 0) return "";
        const int m = maze[0].size();
        const int INF = n * m + 1;
        const int dx[4] = {0, 1, 0, -1};
        const int dy[4] = {1, 0, -1, 0};
        const string dir[4] = {"r", "d", "l", "u"};
        using d_t = pair<int, string>;
        struct n_t {
          int x; int y;
          d_t d;
        };
        auto cd = [](const d_t &l, const d_t &r) {
            if (l.first != r.first) {
                return l.first < r.first;
            }
            return l.second < r.second;
        };
        auto cn = [&cd](const n_t &l, const n_t &r) {
            return cd(l.d, r.d);
        };
        
        vector<vector<d_t>> d(n, vector<d_t>(m, make_pair(INF, "")));
        priority_queue<n_t, vector<n_t>, decltype(cn)> q(cn);
        
        d[ball[0]][ball[1]] = make_pair(0, "");
        q.push((n_t){ball[0], ball[1], make_pair(0, "")});
        
        while (!q.empty()) {
            n_t t = q.top(); q.pop();
            if (t.d != d[t.x][t.y]) continue;
            
            for (int i = 0; i < 4; ++i) {
                int nx = t.x; int ny = t.y;
                while (nx >= 0 && nx < n && 
                       ny >= 0 && ny < m &&
                       maze[nx][ny] == 0 && 
                       !(nx == hole[0] && ny == hole[1])) {
                    nx += dx[i]; ny += dy[i];
                }

                if (!(nx == hole[0] && ny == hole[1])) {
                    nx -= dx[i]; ny -=dy[i];
                    if (nx == t.x && ny == t.y) continue;
                }
                
                n_t nn {nx, ny, 
                        make_pair(t.d.first + abs(nx - t.x) + abs(ny - t.y), 
                                  t.d.second + dir[i])};
                if (cd(nn.d, d[nx][ny])) {
                    d[nx][ny] = nn.d;
                    q.push(nn);
                }
            }
        }
        
        return d[hole[0]][hole[1]].second == "" ? "impossible" : d[hole[0]][hole[1]].second;
    }
};
