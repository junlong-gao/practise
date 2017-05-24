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
        int maxCoins(vector<int>& nums) {
            int n = nums.size();
            nums.insert(nums.begin(), 1);
            nums.push_back(1);
            vector<vector<int>> dp(n+2, vector<int>(n+2,0));
            for(int l = 1; l <= n; ++l){
                for(int i = 1; i + l - 1 <= n; ++i){
                    int j = i + l - 1;
                    for(int k = i; k <= j; ++k){
                        dp[i][j] = max(dp[i][j], dp[i][k-1]+dp[k+1][j]+nums[i-1]*nums[k]*nums[j+1]);
                    }
                }
            }
            return dp[1][n];
        }
    };

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            vector<int> testcase ={3,1,5,8};
            REQUIRE(testObj.maxCoins(testcase) == 167);
		}
	}
}


