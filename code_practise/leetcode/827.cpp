/*
For each 0, we check if it is flipped to 1, what is the new island size by
adding its adjcant connect components.
*/

class Solution {
    vector<vector<int>> g;
    vector<int> comps;
    int id = 1;
    int n, m;
    vector<vector<bool>> visited;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    
    bool isValid(int x, int y) {
        if (x < 0) return false;
        if (y < 0) return false;
        if (x >= n) return false;
        if (y >= m) return false;
        return true;
    }
    
    int flood(int x, int y) {
        g[x][y] = id;
        visited[x][y] = true;
        int ret = 1;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny) && g[nx][ny] == 1 && !visited[nx][ny]) {
                ret += flood(nx, ny);
            }
        }
        return ret;
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        swap(g, grid);
        n = g.size();
        m = g[0].size();
        visited = vector<vector<bool>>(n, vector<bool>(m));
        comps.push_back(0);
        int best = 0;

        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                if (g[x][y] == 1 && !visited[x][y]) {
                    comps.push_back(flood(x, y));
                    best = std::max(best, comps.back());
                    id++;
                }
            }
        }
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                if (g[x][y] != 0) {
                    continue;
                }
                int cur = 1;
                unordered_set<int> neighbour;
                for (int k = 0; k < 4; ++k) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (isValid(nx, ny)) {
                        neighbour.insert(g[nx][ny]);
                    }
                }
                for (auto n : neighbour) {
                    cur += comps[n];
                }
                best = std::max(best, cur);
            }
        }
        return best;
    }
};
