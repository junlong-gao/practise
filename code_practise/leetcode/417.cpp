class Solution {
	vector<vector<int>> reachable;
	int n, m;
	vector<vector<int>> g;
	int dx[4] = {0, 1, 0, -1};
	int dy[4] = {1, 0, -1, 0};
	bool valid(int x, int y) {
		if (x < 0) return false;
		if (x >= n) return false;
		if (y < 0) return false;
		if (y >= m) return false;
		return true;
	}

	void bfs(deque<pair<int, int>> &start) {	
		vector<vector<bool>> visited(n, vector<bool>(m, false));
		for (const auto & pr : start) {
			visited[pr.first][pr.second] = true;
			reachable[pr.first][pr.second] ++;
		}

		while(!start.empty()) {
			auto top = start.front();
			start.pop_front();
			int x = top.first; int y = top.second;
			for (int i = 0; i < 4; ++i) {
				int nx = x + dx[i]; int ny = y + dy[i];
				if (!valid(nx, ny)) continue;
				if (visited[nx][ny]) continue;
/*
XXX2
this is wrong. a node can be reached by some of its surroundings.
how to mitigate:
lack of understanding of how a graph is discovered:
we are performing a bfs on a graph. but we are only trying to discover a subgraph: node is a subset and the edge is a subset.
what we are doing is trying to compute this subgraph on the fly during bfs.
subgraph is defined by a binary function over the nodes: f(x, y) = true <=> x, y and edge xy is in the graph.


				visited[nx][ny] = true;

				if (g[nx][ny] >= g[x][y]) {
					reachable[nx][ny]++;
					start.emplace_back(nx, ny);
				}
*/
				if (g[nx][ny] >= g[x][y]) {
					visited[nx][ny] = true;
					reachable[nx][ny]++;
					start.emplace_back(nx, ny);
				}
			}
		}
	}
public:
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
            if (matrix.empty()) return {};
	n = matrix.size();
	m = matrix[0].size();
	reachable.resize(n, vector<int>(m, 0));
	g = move(matrix);

	// pacific
	deque<pair<int, int>> boundary;
	for (int i = 0; i < m; ++i) {
		boundary.emplace_back(0, i);
	}
	for (int i = 1; i < n; ++i) {
		boundary.emplace_back(i, 0);
	}
	bfs(boundary);

	//boundary.clear();
// altalenta
	for (int i = 0; i < n; ++i) {
		boundary.emplace_back(i, m - 1);
	}
/*
XXX1
look above the code, this is not skipping the right cell
how to mitigate:
focus.
talk aloud to convince.
	for (int i = 1; i < m; ++i) {
*/
	for (int i = 0; i < m - 1; ++i) {
		boundary.emplace_back(n - 1, i);
	}
	bfs(boundary);

	vector<pair<int, int>> ret;
	for (int x = 0; x < reachable.size(); ++x) {
		for (int y = 0; y < reachable[x].size(); ++y) {
			if (reachable[x][y] == 2) {
				ret.emplace_back(x, y);
			}
		}
	}

	return ret;
    }
};

/*
compile error:
int dx -> int dx[4]
visited(nx, ny) XXX

wrong answer:
XXX1:
XXX2:
*/

