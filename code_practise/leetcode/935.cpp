class Solution {
    long long M = 1e9 + 7;
    vector<vector<int>> dp;
    vector<vector<int>> valid_move{
        {4, 6}, //0
        {8, 6}, //1
        {7, 9}, //2
        {4, 8}, //3
        {3, 9, 0}, //4
        {}, //5
        {1, 7, 0}, //6
        {2, 6}, //7
        {1, 3}, //8
        {2, 4}, //9
    };
    
    long long helper(int N, int pos) {
        int & ret = dp[N][pos];
        if (ret != -1) {
            return ret;
        }
        
        if (N == 0) return ret = 1;
        ret = 0;
        for (auto n : valid_move[pos]) {
            ret = ((long long)ret + helper(N - 1, n)) % M;
        }
        
        return ret;
    }
public:
    int knightDialer(int N) {
        dp.resize(N + 1, vector<int>(10, -1));
        
        long long ret = 0;
        for (int i = 0; i < 10; ++i) {
            ret = (ret + helper(N - 1, i)) % M;
        }

        return ret;
    }
};
