#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
	class Solution {
		unordered_map<int, vector<int>> e;
		vector<bool> visited;
		int n;
		bool dfs(int p, int cur){
			auto& neighbours = e[cur];
			for(int i = 0; i < neighbours.size(); ++i){
				int u = neighbours[i];
				if(visited[u] && u!=p){
					return false;
				}else if (!visited[u]){
					visited[u] = true;
					if(!dfs(cur, u)) return false;
				}
			}
			return true;
		}
	public:
		bool validTree(int n, vector<pair<int, int>>& edges) {
			if(edges.size() != n -1) return false;
			this->n = n;
			for(auto& pr: edges){
				e[pr.first].push_back(pr.second);
				e[pr.second].push_back(pr.first);
			}
			visited.resize(n, false);
			if(edges.size() == 0) return true;
			visited[edges.front().first] = true;
			return dfs(-1, edges.front().first);
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


