/*
This can be done in Dijstra's by breaking ties using lex order of the path to the node.
On the other hand, the search space is a dag
*/
class Solution {
	vector<vector<string>> paths;
	vector<vector<int>> dist;
	vector<vector<int>> g;
	int dx[4] = {0, 1, 0, -1};
	int dy[4] = {1, 0, -1, 0};
	string dir[4] = {"r", "d", "l", "u"};
	int n, m;
	int destx; int desty;
	void dfs(int x, int y) {
		for (int i = 0; i < 4; ++i) {
			int nx = x; int ny = y;
			while (nx >= 0 && nx < n && ny >= 0 && ny < m &&
			       g[nx][ny] == 0 && !(nx == destx && ny == desty)) {
				nx += dx[i]; ny += dy[i];
			}

			if (!(nx == destx && ny == desty)) {
				nx -= dx[i]; ny -=dy[i];
				if (nx == x && ny == y) continue;
			} 

			int newDist = dist[x][y] + abs(nx - x) + abs(ny - y);
			if (newDist > dist[nx][ny]) continue;
			string newPath = paths[x][y] + dir[i];
			if (newPath < paths[nx][ny] || newDist < dist[nx][ny]) {
				paths[nx][ny] = newPath;
				dist[nx][ny] = newDist;
				if (!(nx == destx && ny == desty)) {
					dfs(nx, ny);
				}
			}
		}
	}
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
            n = maze.size(); if (n == 0) return "";
	m = maze[0].size();
	const int INF = n * m + 1;
	paths.resize(n, vector<string>(m));
	dist.resize(n, vector<int>(m, INF));
	swap(maze, g);
	destx = hole[0]; desty = hole[1];
	
	dist[ball[0]][ball[1]] = 0;
	paths[ball[0]][ball[1]] = "";
	dfs(ball[0], ball[1]);

	return paths[hole[0]][hole[1]] == "" ? "impossible" : paths[hole[0]][hole[1]];
    }
};

