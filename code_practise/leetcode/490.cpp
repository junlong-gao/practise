class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
	int dx[4] = {0, 1, 0, -1};
	int dy[4] = {1, 0, -1, 0};
	deque<pair<int, int>> q;
	int n = maze.size();
	if (maze.empty()) return false;
	int m = maze[0].size();
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	
	// first:
	q.emplace_back(start[0], start[1]);
	visited[q.front().first][q.front().second] = true;
	// rest:
	while(!q.empty()) {
		auto top = q.front();
		q.pop_front();
		if (top.first == destination[0] && top.second == destination[1]) return true;
		int x = top.first; int y = top.second;
		for (int i = 0; i < 4; ++i) {
			int delta = 1;
			while (true) {
				int nx = x + dx[i] * delta;
				int ny = y + dy[i] * delta;
				if (nx < 0 || nx >= n || ny < 0 || ny >= m || maze[nx][ny]) break;
				delta++;
			}
			int nx = x + dx[i] * (delta - 1);
			int ny = y + dy[i] * (delta - 1);
			if (!visited[nx][ny]) {
				visited[nx][ny] = true;
				q.emplace_back(nx, ny);
			}
		}
	}
	return false;
    }
};
