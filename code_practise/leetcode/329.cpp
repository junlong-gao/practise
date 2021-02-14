class Solution {
    vector<vector<int>> dp;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    int search(int x, int y, vector<vector<int>> &matrix) {
        int &ret = dp[x][y];
        if (ret != -1) {
            return ret;
        }
        
        ret = 1;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= matrix.size() || ny < 0 || ny >= matrix[0].size() || matrix[nx][ny] <= matrix[x][y]) {
                continue;
            }
            
            ret = max(ret, search(nx, ny, matrix) + 1);
        }
        
        return ret;
    }
    
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
       dp.resize(matrix.size(), vector<int>(matrix[0].size(), -1)); 
        int ret = 0;
        for (int x = 0; x < matrix.size(); ++x) {
            for (int y = 0; y < matrix[x].size(); ++y) {
                ret = max(ret, search(x, y, matrix));
            }
        }
        
        return ret;
    }
};