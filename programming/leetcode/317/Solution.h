#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <limits>
#include "catch.hpp"
#include "printer.h"

namespace lee317{
	using namespace std;
	int dx[4] = {-1, 0, 1, 0};
	int dy[4] = {0, -1, 0, 1};
	using grid_t = vector<vector<int>>;
	class Solution{
		bool isValid(grid_t& grid, vector<vector<bool>>& visited, int x, int y){
			if(x < 0 || x >= grid.size()) return false;
			if(y < 0 || y >= grid[x].size()) return false;
			if(visited[x][y]) return false;
			if(grid[x][y] < 0) return false;
			return true;
		}
		
	public:
		int shortestDistance(vector<vector<int>>& grid) {
			for(int x = 0; x < grid.size(); ++x){
				for(int y = 0; y < grid[x].size(); ++y){
					grid[x][y] = -grid[x][y];
				}
			}
			for(int x = 0; x < grid.size(); ++x){
				for(int y = 0; y < grid[x].size(); ++y){
					if(grid[x][y] == -1){
						bfs(x, y, grid);
					}
				}
			}
			int ret = numeric_limits<int>::max();
			for(int x = 0; x < grid.size(); ++x){
				for(int y = 0; y < grid[x].size(); ++y){
					if(grid[x][y] > 0 && grid[x][y] < ret){
						ret = grid[x][y];
					}
				}
			}
			return ret == numeric_limits<int>::max() ? -1:ret;
		}

		void bfs(int x, int y, grid_t& grid){
			grid_t board(grid.size(), vector<int>(grid[0].size(), numeric_limits<int>::max()));
			vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
			deque<pair<int, int>> q;
			q.emplace_back(x, y);
			visited[x][y] = true;
			board[x][y] = 0;
			while(!q.empty()){
				auto top = q.front();
				q.pop_front();
				for(int i = 0; i < 4; ++i){
					int nx = top.first + dx[i];
					int ny = top.second + dy[i];
					if(isValid(grid, visited, nx, ny) && grid[nx][ny] < numeric_limits<int>::max()){
						q.emplace_back(nx, ny);
						visited[nx][ny] = true;
						board[nx][ny] = board[top.first][top.second] + 1;
					}
				}
			}
			for(int x = 0; x < grid.size(); ++x){
				for(int y = 0; y< grid[x].size(); ++y){
					if(grid[x][y] >= 0){
					   grid[x][y]+=board[x][y];
					   if(board[x][y] == numeric_limits<int>::max()){
							grid[x][y] = board[x][y];
						}	
					}
				}
			}
		}
	};


	TEST_CASE("smoke 317"){
		Solution testObj;
		SECTION("sample 0"){
			grid_t testcase = {{1,0,2,0,1},{0,0,0,0,0},{0,0,1,0,0}};
			REQUIRE(
				testObj.shortestDistance(testcase) == 7
			);
		}
		SECTION("sample 1"){
			grid_t testcase = {{1},{2}};
			REQUIRE(
				testObj.shortestDistance(testcase) == -1
			);
		}
		SECTION("sample 2"){
			grid_t testcase = {{1, 1, 0, 0, 2, 1},{0,0,1,2,2,1}, {1,0,1,0,2,1}};
			REQUIRE(
				testObj.shortestDistance(testcase) == -1
			);
		}
		SECTION("sample 3"){
			grid_t testcase = {{1, 1, 0, 0, 0, 1},{0,0,0,2,0,1}, {1,0,1,0,0,1}};
			REQUIRE(
				testObj.shortestDistance(testcase) == 23
			);
		}
		SECTION("sample 4"){
			grid_t testcase = {{1, 0, 0},{0,2,2}, {1,0,0}};
			REQUIRE(
				testObj.shortestDistance(testcase) == 2
			);
		}
	}
}
