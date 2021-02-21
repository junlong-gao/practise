class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
	for (int i = 0; i < A.size(); ++i) {
		// of the same rank, arithmetic and comparison is cast to unsigned.
    // this is not issue for compute, but problematic for compare size
		for (int j = 0; j <= (int)(A[i].size()) - 1 - j; ++j) { // cast to unsigned
			A[i][j] = (A[i][j] + 1) % 2;
			if (j < A[i].size() - 1 - j) {
				swap(A[i][j], A[i][A[i].size() - j - 1]);
				A[i][j] = (A[i][j] + 1) % 2;
			}
		}
	}
	return A;
    }
};

