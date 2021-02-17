class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        vector<vector<int>> up(matrix.size(), vector<int>(matrix[0].size(), 0));
        vector<vector<int>> left(matrix.size(), vector<int>(matrix[0].size(), 0));
        vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), 0));
        int tot = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] == 0) {
                    up[i][j] = 0;
                    left[i][j] = 0;
                } else {
                    if (i == 0) {
                        up[i][j] = 1;
                    } else {
                        up[i][j] = 1 + up[i-1][j];
                    }
                    if (j == 0) {
                        left[i][j] = 1;
                    } else {
                        left[i][j] = 1 + left[i][j-1];
                    }
                }
            }
        }

        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (i == 0 || j == 0) {
                    dp[i][j] = matrix[i][j];
                } else if (matrix[i][j] == 1) {
                    dp[i][j] = min(up[i][j], min(left[i][j], dp[i-1][j-1] + 1));
                }
                tot += dp[i][j];
            }
        }
        return tot;
    }
};