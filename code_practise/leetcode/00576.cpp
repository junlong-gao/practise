class Solution {
    template<typename T>
    using v = vector<T>;
    using ll = long long;
    const ll M = 1e9 + 7;
    
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    v<v<v<ll>>> dp{51, v<v<ll>>{51, v<ll>(51, -1)}};
public:
    int findPaths(int m, int n, int N, int i, int j) {
        if (i < 0 || i >= m || j < 0 || j >= n) {
            return 1;
        }
        if (N == 0) return 0;
        
        //cout << i << " " << j << " " << N << endl;
        ll &ret = dp[i][j][N];   
        if (ret >= 0) {
            return ret;
        }
        ret = 0;
        for (int k = 0; k < 4; ++k) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            ret = (ret + findPaths(m, n, N - 1, ni, nj)) % M;
        }
        
        return ret;
    }
};
