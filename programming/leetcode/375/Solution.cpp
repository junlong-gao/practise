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
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
	class Solution {
	public:
		int getMoneyAmount(int n) {
			if(n == 2) return 1;
			if(n <= 1) return 0;
			vector<vector<int>> dp(n, vector<int>(n, 0));
			for(int l = 2; l <= n; ++l){
				for(int i = 0; i + l - 1 < n; ++i){
					int j = i + l - 1;
					if(l == 2){
						dp[i][j] = i + 1;
					}else{
						int t = numeric_limits<int>::max();
						for(int k = i+1; k <= j-1; ++k){
							t = min(t, max(dp[i][k-1]+k+1, dp[k+1][j]+k+1));
						}
						dp[i][j] = t;
					}
				}
			}
			return dp[0][n-1];
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


