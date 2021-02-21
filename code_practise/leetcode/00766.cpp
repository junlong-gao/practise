// Take 1:
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return true;
        int m = matrix[0].size();
        for (int i = n - 1; i >= 0; --i) {
          int val = matrix[i][0];
          for (int j = 1; i + j < n && j < m; ++j) {
            if (matrix[i + j][j] != val) return false;
          }
        }
        
        for (int j = 1; j < m; ++j) {
          int val = matrix[0][j];
          for (int i = 1; i < n && i + j < m ; i++) {
            if(matrix[i][i + j] != val) return false;
          }
        }
        return true;
    }
};

// Take 2:
// consider each element and its top left
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix)  {
        for (int r = 0; r < matrix.length; ++r)
            for (int c = 0; c < matrix[0].length; ++c)
                if (r > 0 && c > 0 && matrix[r-1][c-1] != matrix[r][c])
                    return false;
        return true;
    }
}
