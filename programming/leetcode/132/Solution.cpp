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
        int minCut(string s) {
            int n = s.length();
            vector<vector<bool>> dp(n+1, vector<bool>(n+1, true));
            for(int l = 2; l <= n; ++l){
                for(int i = 1; i + l - 1 <= n; ++i){
                    int j = i + l - 1;
                    dp[i][j] = (s[i-1] == s[j-1]) && (dp[i+1][j-1]);
                    //cout << i << " " << j << " " << dp[i][j] << "\n";
                }
                //cout << endl;
            }
            vector<vector<int>> t(n+1, vector<int>(n+1, 0));
            for(int l = 2; l <=n; ++l){
                for(int i = 1; i + l - 1<=n; ++i){
                    int j = i + l - 1;
                    if(dp[i][j]) t[i][j] = 0;
                    else{
                        t[i][j] = numeric_limits<int>::max();
                        for(int k = i; k < j; ++k){
                            t[i][j] = min(t[i][j], t[i][k] + t[k+1][j] + 1);
                        }
                    }
                }
            }
            return t[1][n];
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            REQUIRE(testObj.minCut("aabb") == 1);
            REQUIRE(testObj.minCut("abc") == 2);
		}
	}
}


