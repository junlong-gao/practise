class Solution {
    /*
    up(i, j) : highest i' such that [i, j]...[i', j] is 1
    left(i, j) : smallest j' such that up(i, j) is maintained
    right(i, j) : largest j'
    
    up(i, j) = up(i - 1, j) + 1 if (i, j) is 1, 0 otherwise
    left(i, j) = max(left(i - 1, j), last continous 1 on the left)
    */
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        vector<int> up(matrix[0].size(), 0);
        vector<int> left(matrix[0].size(), 0);
        vector<int> right(matrix[0].size(), matrix[0].size() - 1);
        
        int ret = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            int lastLeft = 0;
            for (int j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] == '1') {
                    up[j] = up[j] + 1;
                    if (i > 0 && matrix[i-1][j] == '1') {
                        left[j] = max(lastLeft, left[j]);
                    } else {
                        left[j] = lastLeft;
                    }
                } else {
                    up[j] = 0;
                    //left[j] = 0;
                    lastLeft = j + 1;
                }
            }
            
            int lastRight = matrix[i].size() - 1;
            for (int j = matrix[i].size() - 1; j >= 0; --j) {
                if (matrix[i][j] == '1') {
                    if (i > 0 && matrix[i-1][j] == '1') {
                        right[j] = min(lastRight, right[j]);
                    } else {
                        right[j] = lastRight;
                    }
                } else {
                    //right[j] = matrix[i].size() - 1;
                    lastRight = j - 1;
                }
                ret = max(ret, up[j] * (right[j] - left[j] + 1));
            }
        }
        
        return ret;
    }
};
