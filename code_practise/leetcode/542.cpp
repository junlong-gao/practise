class Solution {
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        struct p {
            int x, y, d;  
        };
        deque<p> q;
        int n = matrix.size();
        if (n == 0) return {};
        int m = matrix[0].size();
        vector<vector<int>> ret(n, vector<int>(m, 0));
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] == 0) {
                    visited[i][j] = true;
                    q.push_back({i, j, 0});
                }
            }
        }
        while (q.size()) {
            auto top = q.front(); q.pop_front();
            for (int i = 0; i < 4; ++i) {
                int nx = top.x + dx[i];
                int ny = top.y + dy[i];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                    !visited[nx][ny] && 
                    matrix[nx][ny] == 1) {
                    int d = top.d + 1;
                    ret[nx][ny] = d;
                    visited[nx][ny] = true;
                    q.push_back({nx, ny, d});
                }
            }
        }
        return ret;
    }
};
