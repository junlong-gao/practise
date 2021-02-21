class Solution {
    /*
    dp[i][j] = max square side cornered at m[i][j]
    */
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        vector<int> cur(matrix[0].size(), 0);
        int ret = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            vector<int> n(matrix[i].size(), 0);
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (i == 0) {
                    n[j] = matrix[i][j] == '1';
                } else if (j == 0) {
                    n[j] = matrix[i][j] == '1';
                } else {
                    if (matrix[i][j] == '0') {
                        n[j] = 0;
                    } else {
                        n[j] = min(n[j-1], min(cur[j], cur[j-1])) + 1;
                    }
                }
                ret = max(ret, n[j]);
            }
            swap(cur, n);
        }
        return ret * ret;
    }
};
