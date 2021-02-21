class Solution {
public:
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        int n = A.size();
	if (n == 0) return 0;
	int m = A[0].size();
	int best = 0;
	for (int dx = -n + 1; dx < n; ++dx) { for (int dy = -m + 1; dy <= m; ++dy) {
		int t = 0;
		for (int i = 0; i < n; ++i) { for (int j = 0; j < m; ++j) {
			if (i + dx < 0 || i + dx >= n) {continue;}
			if (j + dy < 0 || j + dy >= m) {continue;}
			if (A[i][j] && B[i + dx][j + dy]) t++;
		}}
		best = max(best, t);
	}}
	return best;
    }
};

/*
Easy
*/

