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
        bool isInterleave(string s1, string s2, string s3) {
            if(s1.length() + s2.length() != s3.length()) return false;
            vector<vector<bool>> dp(s1.size() + 1, vector<bool>(s2.size() + 1, false));
            dp[0][0] = true;
            for(int i = 0; i <= s1.size(); ++i){
                for(int j = 0; j <= s2.size(); ++j){
                    if(!i && !j) continue;
                    if(i > 0) dp[i][j] = dp[i][j] || (s1[i-1] == s3[i+j-1] && dp[i-1][j]);
                    if(j > 0) dp[i][j] = dp[i][j] || (s2[j-1] == s3[i+j-1] && dp[i][j-1]);
                }
            }
            return dp[s1.length()][s2.length()];
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


