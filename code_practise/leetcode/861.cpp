class Solution {
public:
    int matrixScore(vector<vector<int>>& A) {
        int ret = 0;
        if (A.empty() || A[0].empty()) return ret;
        for (int i = 0; i < A.size(); ++i) {
            if (A[i][0] == 0) {
                for (int j = 0; j < A[i].size(); ++j) {
                    A[i][j] = 1 - A[i][j];
                }
            }
        }
        
        for (int j = 0; j < A[0].size(); ++j) {
            int col = 0;
            for (int i = 0; i < A.size(); ++i) {
                col += A[i][j];
            }
            col = max(col, static_cast<int>(A.size()) - col);
            ret += col * (1 << (A[0].size() - j - 1));
        }
        return ret;
    }
};
