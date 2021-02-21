class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) return false;
        int x = 0; int y = matrix[0].size() - 1;
        while (x < matrix.size() && y >= 0) {
            if (target > matrix[x][y]) {x++;}
            else if (target < matrix[x][y]) {y--;}
            else {return true;}
        }
        return false;
    }
};