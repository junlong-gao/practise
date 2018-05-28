class Solution {
public:
    bool judgeCircle(string moves) {
        	int dx[4] = {0, 1, 0, -1};
        	int dy[4] = {1, 0, -1, 0};
	int x = 0; int y = 0;
	unordered_map<char, int> m {{'D', 0}, {'R', 1}, {'U', 2}, {'L', 3}};
	for (auto c : moves) {
		x +=dx[m[c]];
		y += dy[m[c]];
	}
	return x == 0 && y == 0;
    }
};

