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
		int total = 0;
		int half = 0;
		unordered_map<TreeNode*, unordered_map<bool, int>> opt;
		int dfs(TreeNode* root, bool p){
			if(root == NULL) return 0;
			if(opt[root][p] == 0){
				opt[root][p] = dfs(root->left, false) + dfs(root->right, false);
				if(!p){
					opt[root][p] = max(opt[root][p], dfs(root->left, true) + dfs(root->right, true) + root->val);
				}
				return opt[root][p];
			}else{
				return opt[root][p];
			}
		}
	public:
		int rob(TreeNode* root) {
			if(root == NULL ) return 0;
			dfs(root, false);
			dfs(root, true);

			return max(opt[root][true], opt[root][false]);
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


