class Solution {
public:
    int longestLine(vector<vector<int>>& M) {
	int n = M.size();
	if (n == 0) return 0;
	int m = M[0].size();
	int best = 0;

	for (int i = 0; i < n; ++i) {
		int run = 0;
		for (int j = 0; j < m; ++j) {
			if (M[i][j] == 0) run = M[i][j];
			else run++;
			best = max(best, run);
		}
	}

	for (int j = 0; j < m; ++j) {
		int run = 0;
		for (int i = 0; i < n; ++i) {
			if (M[i][j] == 0) run = M[i][j];
			else run++;
			best = max(best, run);
		}
	}

	for (int l = 1 - n; l < m; l++) {
		int run = 0;
		for (int x = 0; x < n; ++x) {
			int y = x + l;
			if (y < 0 || y >= m) continue;
			if (M[x][y] == 0) run = M[x][y];
			else run++;
			best = max(best, run);
		}
	}

	for (int l = 0; l < n + m - 1; l++) {
		int run = 0;
		for (int x = 0; x < n; ++x) {
			int y = -x + l;
			if (y < 0 || y >= m) continue;
			if (M[x][y] == 0) run = M[x][y];
			else run = run + 1;
			best = max(best, run);
		}
	}

	return best;
    }
};

/*
primary, secondary diag
*/



