class Solution {
    int helper(int p, vector<int> &x, vector<int> &y) {
        assert(x.size() && x.size() == y.size());
        int count = 1;
        int rotate = (p == x[0] ? 0 : 1);
        for (int i = 1; i < x.size(); ++i) {
            if (y[i] == p || x[i] == p) {
                count++;
            }
                            
            if (y[i] == p && x[i] != p) {
                rotate++;
            }
        }
        if (count != x.size()) {
            return INT_MAX;
        }
        return rotate;
    }

public:
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        int a = min(helper(A[0], A, B), helper(B[0], A, B));
        int b = min(helper(A[0], B, A), helper(B[0], B, A));
        if (a == INT_MAX && b == INT_MAX) {
            return -1;
        }
        if (a == INT_MAX) {
            return b;
        }
        if (b == INT_MAX) {
            return a;
        }
        return min(a, b);
    }
};