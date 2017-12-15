#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
    class Solution {
    public:
        int maxKilledEnemies(vector<vector<char>>& grid) {
            if(grid.size() == 0) return 0;
            vector<vector<int>> left(grid.size(), vector<int>(grid[0].size(), 0));
            vector<vector<int>> right(grid.size(), vector<int>(grid[0].size(), 0));
            vector<vector<int>> up(grid.size(), vector<int>(grid[0].size(), 0));
            vector<vector<int>> down(grid.size(), vector<int>(grid[0].size(), 0));
            
            int cur = 0;
            for(int i = 0; i < grid.size(); ++i){
                for(int j = 0; j < grid[i].size(); ++j){
                    if(grid[i][j] == 'W') continue;
                    left[i][j] = (j==0? 0 : left[i][j-1]) + ((grid[i][j]=='E')?1:0);
                    up[i][j] = (i==0? 0 : up[i-1][j]) + ((grid[i][j]=='E')?1:0);
                }
            }
            for(int i = grid.size() - 1; i >= 0; --i){
                for(int j = grid[i].size() - 1; j >= 0; --j){
                    if(grid[i][j] == 'W') continue;
                    right[i][j] = (j == grid[i].size()-1? 0:right[i][j+1]) + ((grid[i][j]=='E')?1:0);
                    down[i][j] = (i == grid.size()-1? 0:down[i+1][j]) + ((grid[i][j]=='E')?1:0);
                }
            }
            for(int i = 0; i < grid.size(); ++i){
                for(int j = 0; j < grid[i].size(); ++j){
                    if(grid[i][j] == '0'){
                        cur = max(cur, left[i][j]+right[i][j]+up[i][j]+down[i][j]);
                    }
                }
            }
            
            return cur;
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
		SECTION("sample"){

		}
	}
}


