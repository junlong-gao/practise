class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        if (A.empty()) return A;
        int m = abs(A[0]); int idx = 0;
        for (int i = 1; i < A.size(); ++i) {
            if (abs(A[i]) < m) {
                idx = i;
                m = abs(A[i]);
            }
        }
        
        int i = idx, j = i + 1;
        vector<int> ret;
        while (i >= 0 && j < A.size()) {
            if (abs(A[i]) < abs(A[j])) {
                ret.push_back(A[i] * A[i]);
                i--;
            } else {
                ret.push_back(A[j] * A[j]);
                j++;
            }
        }
        
        while (i >= 0) {
            ret.push_back(A[i] * A[i]); i--;
        }
        while (j < A.size()) {
            ret.push_back(A[j] * A[j]); j++;
        }
        
        return ret;
    }
};
