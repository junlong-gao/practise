class Solution {
    int norm(int x, int y, int ny) {
        return x * ny + y;
    }
public:
    int countServers(vector<vector<int>>& grid) {
        unordered_map<int, unordered_set<int>> p;
        unordered_map<int, unordered_set<int>> q;
        vector<bool> bs(grid.size() * grid[0].size(), false);
        
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == 0) continue;
                if (p[i].size() > 0 || q[j].size() > 0) {
                    bs[norm(i,j,grid[0].size())] = true;
                }
                if (p[i].size() > 0) {
                    bs[norm(i,*p[i].begin() ,grid[0].size())] = true;
                }
                if (q[j].size() > 0) {
                    bs[norm(*q[j].begin() , j, grid[0].size())] = true;
                }
                p[i].insert(j);
                q[j].insert(i);
            }
        }
        
        int ret = 0;
        for (int i = 0; i < bs.size(); ++i) {
            if (bs[i]) {
                ret++;
            }
        }
        
        return ret;
    }
};