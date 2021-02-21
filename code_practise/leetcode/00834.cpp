/*
dfs exploring a tree:
think in terms of:
- the edge that leads you to the node
- all the rest edges going out from the node
*/
class Solution {
	unordered_map<int, vector<int>> g;
	unordered_map<int, vector<int>> t;
	vector<bool> visited;

	vector<int> acc; // total dist for all nodes in a subtree
	vector<int> sizes; //  total number of nodes in a subtree
	vector<int> ans;
	int r, n;

	int sizer(int root) {
		int & ret = sizes[root];
		ret = 1;
		for (auto & c : g[root]) {
			ret += sizer(c);
		}
		return ret;
	}

	int f(int root) {
		int & ret = acc[root];
		ret = 0;
		for (auto & c : g[root]) {
			ret += f(c) + sizes[c];
		}
		return ret;
	}

	void dist(int root, int count) {
		int & total = ans[root];
		total = count + acc[root];
		for (auto & c : g[root]) {
			// now the interesting part:
			int newCount = count + n - sizes[root] + 
					  sizes[root] - sizes[c] + acc[root] - (acc[c] + sizes[c]);
			dist(c, newCount);
		}
	}
	
	void make_tree(int root) {
		for (auto c : t[root]) {
			if (visited[c]) continue;
			g[root].push_back(c);
			visited[c] = true;
			make_tree(c);
		}
	}

public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
	n = N;
	visited.resize(N, false);
	ans.resize(N, 0);
	sizes.resize(N, 0);
acc.resize(N, 0);

	for (int i = 0; i < edges.size(); ++i) {
		t[edges[i][0]].push_back(edges[i][1]);
		t[edges[i][1]].push_back(edges[i][0]);
	}
visited[0] = true;
make_tree(0);

	// find all subtree size:
	sizer(0);
	// find all subtree's nodes distance
	f(0);
	// the prize:
	dist(0, 0);

	return ans;
     }
};

