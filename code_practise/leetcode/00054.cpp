class Solution {
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int i = 0;
        int n = matrix.size();
        if (n == 0) { return {}; }
        n *= matrix[0].size();
        int x = 0; int y = 0;
        vector<int> ret;
        while (n-->0) {
            ret.push_back(matrix[x][y]);
            int nx = x + dx[i%4];
            int ny = y + dy[i%4];
            matrix[x][y] = 101;
            if (nx >= matrix.size() || nx < 0 || ny >= matrix[0].size() || ny < 0 || matrix[nx][ny] == 101) {
                i++;
                nx = x + dx[i%4];
                ny = y + dy[i%4];
            }
            x = nx;
            y = ny;
        
        }
        return ret;
    }
};