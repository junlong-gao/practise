class NumMatrix {
    vector<vector<int>> s;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        if(matrix.empty()) return;
        s.resize(matrix.size() + 1);
        for (auto & r : s) {
            r.resize(matrix[0].size() + 1, 0);
        }
        
        for (int i = 1; i < s.size(); ++i) {
            vector<int> t(matrix[i - 1].size() + 1, 0);
            
            for (int j = 1; j < t.size(); ++j) {
                t[j] = t[j - 1] + matrix[i - 1][j - 1];
            }
            for (int j = 1; j < t.size(); ++j) {
                s[i][j] = s[i - 1][j] + t[j - 1] + matrix[i - 1][j - 1];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return s[row2 + 1][col2 + 1] - 
                s[row2 + 1][col1]- 
                s[row1][col2 + 1] +
                s[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
