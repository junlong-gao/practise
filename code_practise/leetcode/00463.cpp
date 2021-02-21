/*
start with first land
for each land node
   for each direction
	if it is out of bound or water, count edge
	else (it is island), if not visted, enqueue
*/
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
	int n = grid.size();
	if (n == 0) return 0;
	int m = grid[0].size();

	for (int x = 0; x < n; ++x) { for (int y = 0; y < m; ++y) {
		if (grid[x][y] == 0) continue;
		deque<pair<int, int>> q;
		vector<vector<bool>> visited(n, vector<bool>(m, false));
int count = 0;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
		q.emplace_back(x, y);
		visited[x][y] = true;
		while(!q.empty()) {
			auto top = q.front();
			q.pop_front();
			for (int i = 0; i < 4; ++i) {
				int nx = top.first + dx[i]; int ny = top.second + dy[i];
				if (nx < 0 ||nx >= n || ny < 0 || ny >= m || grid[nx][ny] == 0) {
					count ++;
				} else if (!visited[nx][ny]) {
					visited[nx][ny] = true;
					q.emplace_back(nx, ny);
				}
			}
		}
		return count;
}}
	return 0;
    }
};

/*
compile error
comma.
wa:
check not visited.
*/

