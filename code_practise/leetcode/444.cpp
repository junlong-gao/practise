/*
bfs topo sort can 
- find cycle
- check the sort is unique or not
*/
class Solution {

public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
unordered_map<int, int> indegree;
	unordered_map<int, vector<int>> g;
        	for (int i = 0; i < seqs.size(); ++i) {
		for (int j = 1; j < seqs[i].size(); ++j) {
			g[seqs[i][j]].push_back(seqs[i][j-1]);
			indegree[seqs[i][j - 1]]++;
		}
		if (!seqs[i].empty()) {
			indegree[seqs[i].back()] += 0;
		}
	}
	const int n = indegree.size(); // total number of nodes
	if (org.size() != n) return false;
	for (auto pr : g) {
		if (pr.first >= 1 && pr.first <= n) {continue;}
		return false;
	}

	deque<int> q;
	// now for each node:
	for (int i = 1; i <= n; ++i) {
		if (indegree[i] == 0) { q.push_back(i); }
	}

	// topological sort
	deque<int> constructed;
	while (!q.empty()) {
		if (q.size() > 1) return false; // we have more than one choice

		auto top = q.front(); q.pop_front();
		constructed.push_front(top);

		for (auto next : g[top]) {
			indegree[next]--;
			if (indegree[next] < 0) return false; // cycle
			if (indegree[next] == 0) q.push_back(next);
		}
	}

	// without cycle, topo sort must not be longer than n:
	assert(constructed.size() <= n);
	
	if (constructed.size() != org.size()) return false;
	if (constructed.size() != n) return false;
	for (int i = 0; i < n; ++i) {
		if (org[i] != constructed[i]) return false;
	}

	return true;
    }
};

/*
1 2
 2 1
*/
/*
1 2 3
 2 1
*/

