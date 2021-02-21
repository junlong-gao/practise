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
        int numWays(int n, int k) {
            if(n == 0) return 0;
            vector<vector<int>> dp(n+1, vector<int>(2, 0));
            dp[0][0] = 0;
            dp[0][1] = 0;
            dp[1][0] = k;
            dp[1][1] = 0;
            for(int i = 2; i <= n; ++i){
                dp[i][0] = (k-1)*dp[i-1][0] + (k-1)*dp[i-1][1];
                dp[i][1] = dp[i-1][0];
            }
            return dp[n][0] + dp[n][1];
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


