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
    public:
        int numDistinct(string s, string t) {
            int n = s.length(), m = t.length();
            vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
            for(int i = 0; i <= n; ++i){
                for(int j = 0; j <= m; ++j){
                    if(!i&&!j){
                        dp[i][j] = 1;
                        continue;
                    }
                    if(i == 0 && j){
                        dp[i][j] = 0;
                        continue;
                    }
                    if(j == 0 && i){
                        dp[i][j] = 1;
                        continue;
                    }
                    dp[i][j] = dp[i-1][j] + (s[i-1] == t[j-1]? dp[i-1][j-1]:0);
                }
            }
            return dp[n][m];
        }
    };

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            REQUIRE(testObj.numDistinct("","") == 1);
		}
	}
}


