/*
Dijkstra's
*/
class Solution {
public:
int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& dest) {
	int n = maze.size();
	if (n == 0) return 0;
	int m = maze[0].size();
	
	int dx[4] = {0, 1, 0, -1};
	int dy[4] = {1, 0, -1, 0};
	struct P {
		int x; int y;
		int d;
	};
	auto cmp = [&] (const P &l, const P &r) {
		if (l.d != r.d) return l.d > r.d;
		if (l.x != r.x) return l.x < r.x;
		return l.y < r.y;
	};
	const int INF = n * m + 1;
	priority_queue<P, vector<P>, decltype(cmp)> q(cmp);
	auto d = vector<vector<int>> (n, vector<int>(m, INF));

	q.push({start[0], start[1], 0});
	d[start[0]][start[1]] = 0;
	
	while (!q.empty()) {
		auto top = q.top(); q.pop();
		assert(d[top.x][top.y] <= top.d);
		if (d[top.x][top.y] != top.d) continue;
		if (top.x == dest[0] && top.y == dest[1]) return top.d;
		for (int i = 0; i < 4; ++i) {
			int l = 1; int nx = top.x + dx[i] * l; int ny = top.y + dy[i] * l;
			while (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] == 0) { 
l++;
nx = top.x + dx[i] * l;
ny = top.y + dy[i] * l;
}
			if (l == 1) continue;
			nx = top.x + dx[i] * (l - 1);
			ny = top.y + dy[i] * (l - 1);
			if (d[nx][ny] > top.d + l - 1) {
				d[nx][ny] = top.d + l - 1;
				q.push({nx, ny, d[nx][ny]});
			}
		}
	}
	return -1;
}
};

