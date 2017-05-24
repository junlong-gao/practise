#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <limits>
#include "catch.hpp"
#include "printer.h"

namespace prob_3{
	using namespace std;
	using grid_t = vector<vector<int>>;
	using mask_t = vector<vector<bool>>;
	class Solution{
		vector<bool> unvisited;
		vector<int> p, children;
	public:
		int dfs(int u, grid_t& G){
			int n_children = 0;

			for(int i = 0; i < G[u].size(); ++i){
				if(G[u][i] > 0 && unvisited[i]){
					unvisited[i] = false;
					p[i] = u;
					n_children += dfs(i, G);
				}
			}
			children[u] = n_children;
			return n_children + 1;
		}
		int all_pair_shortest(grid_t& G){
			unvisited.resize(G.size(), true);
			p.resize(G.size());
			children.resize(G.size());
			p[0] = 0;
			unvisited[0] = false;
			dfs(0, G);

			int ret = 0;
			for(int i = 0; i < G.size(); ++i){
				if(p[i]!=i){
					ret += G[i][p[i]] 
							* (children[i] + 1)
							* (G.size() - 1 - children[i]);
				}
			}
			return ret;
		}
	};


	TEST_CASE("all pair shortest smoke"){
		Solution testObj;
		SECTION("sample 1"){
			grid_t G({
				{ -1, 2, -1, -1},
				{ 2, -1, 3, -1},
				{ -1, 3, -1, 4},
				{ -1, -1, 4, -1}
			});
			REQUIRE(testObj.all_pair_shortest(G) == 30);
		}
		SECTION("sample 2"){
			grid_t G({
				{ -1, 1, -1, -1},
				{ 1, -1, 2, 3},
				{ -1, 2, -1, -1},
				{ -1, 3, -1, -1}
			});
			REQUIRE(testObj.all_pair_shortest(G) == 18);
		}
	}
}
