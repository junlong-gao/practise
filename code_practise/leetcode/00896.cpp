class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        int sign = 0;
        for (int i = 1; i < A.size(); ++i) {
            if (A[i] - A[i - 1]) {
                if (sign == 0) {
                    sign = A[i] - A[i - 1];
                    continue;
                } else {
                    if (sign * (A[i] - A[i - 1]) < 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
