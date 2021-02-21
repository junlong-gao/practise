class Solution {
    vector<vector<bool>> g;
    vector<vector<int>> l, r, u, d;
    
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        vector<vector<bool>> g(N, vector<bool>(N, false));
        vector<vector<int>> t(N, vector<int>(N, 0));
        vector<vector<int>> l = t, r = t, u = t, d = t;
        for (int i = 0; i < mines.size(); ++i) {
            g[mines[i][0]][mines[i][1]] = true;
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (g[i][j]) continue;
                
                if (j == 0) l[i][j] = 1;
                else l[i][j] = l[i][j - 1] + 1;
            }
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = N - 1; j >= 0; --j) {
                if (g[i][j]) continue;
                
                if (j == N - 1) r[i][j] = 1;
                else r[i][j] = r[i][j + 1] + 1;
            }
        }
        
        for (int j = 0; j < N; ++j) {
            for (int i = 0; i < N; ++i) {
                if (g[i][j]) continue;
                
                if (i == 0) u[i][j] = 1;
                else u[i][j] = u[i - 1][j] + 1;
            }
        }
        
        for (int j = 0; j < N; ++j) {
            for (int i = N - 1; i >= 0; --i) {
                if (g[i][j]) continue;
                
                if (i == N - 1) d[i][j] = 1;
                else d[i][j] = d[i + 1][j] + 1;
            }
        } 
        
        int k = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (g[i][j]) continue;
                
                k = max(k, min(l[i][j],
                            min(r[i][j],
                               min(d[i][j], u[i][j]))));
            }
        }
        return k;
    }
};
