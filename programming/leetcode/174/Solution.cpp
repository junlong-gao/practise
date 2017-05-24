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
        int flat_min(int x){
            if(x <= 0) return 1;
            return x;
        }
    public:
        int calculateMinimumHP(vector<vector<int>>& dungeon) {
            if(dungeon.size() == 0) return 0;
            int inf = numeric_limits<int>::max();
            int n = dungeon.size();
            int m = dungeon[0].size();
            vector<vector<int>> dp(n+1, vector<int>(m+1, inf));
            for(int i = n - 1; i >=0; --i){
                for(int j = m - 1; j >= 0; --j){
                    if(i == n-1&& j == m-1){
                        dp[i][j] = dungeon[i][j]>=0?1:(1-dungeon[i][j]);
                    }else{
                        dp[i][j] = flat_min(min(dp[i+1][j], dp[i][j+1])- dungeon[i][j]) ;
                    }
                    //cout << min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j] << " " << dp[i][j] << endl;
                    
                }
            }
            return dp[0][0];
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
        SECTION("sample"){
            vector<vector<int>> test{
                {-1, -2},
                {2, 3}
            };
            REQUIRE(testObj.calculateMinimumHP(test)==2);
		}
	}
}


