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
        int target;
        vector<vector<int>> rst;
        
        void helper(vector<int>& sofar, int sum, TreeNode* u){
            if(u == NULL) return;
            int cur = sum + u->val;
            sofar.push_back(u->val);
            if((u->left == NULL) && (u->right == NULL) && cur == target){
                rst.push_back(sofar);
            }else{
                helper(sofar, cur, u->left);
                helper(sofar, cur, u->right);
            }
            sofar.pop_back();
        }
    public:
        vector<vector<int>> pathSum(TreeNode* root, int sum) {
            target = sum;
            vector<int> sofar{};
            helper(sofar, 0, root);
            return rst;
        }
        
    };
    
    TEST_CASE("tests"){
        Solution testObj;
		SECTION("sample"){

		}
	}
}


