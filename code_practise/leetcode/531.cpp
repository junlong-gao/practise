class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        	vector<int> row, col;
	int n = picture.size();
	if (n == 0) return 0;
	int m = picture[0].size();

	row.resize(n, 0); col.resize(m, 0);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (picture[i][j] == 'B') {
				row[i]++; col[j]++;
			}
		}
	}

	int count = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (picture[i][j] == 'B') {
				if (row[i] == 1 && col[j] == 1) {
					count++;
				}
			}
		}
	}
	return count;
    }
};

