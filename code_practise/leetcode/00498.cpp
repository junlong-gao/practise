class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
            int n = matrix.size();
	if (n == 0) return {};
	int m = matrix[0].size();
	vector<int> ret;
	int dir = 0;
	for (int i = 0; i < n + m - 1; ++i) {
		vector<int> cur;
for (int x = min(i, n - 1), y = i - x; x >= 0 && y < m; --x) {
			cur.push_back(matrix[x][i - x]);
		}
		if (dir++ % 2) {
			reverse(cur.begin(), cur.end());
		}
		ret.insert(ret.end(), cur.begin(), cur.end());
	}
	return ret;
    }
};

