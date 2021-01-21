class Solution {
    vector<vector<int>> prev = {
        {4, 6},
        {6, 8},
        {7, 9},
        {4, 8},
        {3, 9, 0},
        {},
        {1, 7, 0},
        {2, 6},
        {1, 3},
        {2, 4},
    };
    
    vector<vector<int>> dp;
    const int M = 1e9+7;
    
    int search(int n, int pos) {
        if (dp[n][pos] != -1) {
            return dp[n][pos];
        }
        int &ret = dp[n][pos];
        
        ret = 0;
        if (n == 1) {
            return ret = 1;
        }
        for (int ppos : prev[pos]) {
            ret = (ret + search(n - 1, ppos)) % M;
        }
        
        return ret;
    }
public:
    int knightDialer(int n) {
        dp.resize(n + 1, vector<int>(10, -1));
        int ret = 0;
        for (int i = 0; i < 10; ++i) {
            ret =  (ret + search(n, i)) % M;
        }
        
        return ret;
    }
};
