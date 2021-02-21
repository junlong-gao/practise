class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int K) {
        int n = mat.size(); int m = mat[0].size();
        vector<vector<int>> p(n, vector<int>(m, 0));
        for (int i = 0; i < n; ++i) {
            int cur = 0;
            for (int j = 0; j < m; ++j) {
                cur += mat[i][j];
                p[i][j] = ((i == 0) ? 0 : p[i-1][j]) + cur;
            }
        }
        
        vector<vector<int>> ans(n, vector<int>(m, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int ik = min(i+K, n-1);
                int jk = min(j+K, m-1);
                ans[i][j] = p[ik][jk];
                if (j-K-1>=0) {
                    ans[i][j] -= p[ik][j-K-1];
                }
                if (i-K-1>=0) {
                    ans[i][j] -= p[i-K-1][jk];
                }
                if (j-K-1>=0 && i-K-1>=0) {
                    ans[i][j] += p[i-K-1][j-K-1];
                }
            }
        }
        return ans;
    }
};