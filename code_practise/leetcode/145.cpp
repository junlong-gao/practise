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
        vector<int> postorderTraversal(TreeNode* root) {
            vector<TreeNode*> s;
            vector<int> rst;
            if(root == NULL) return rst;
            s.push_back(root);
            while(!s.empty()){
                auto top = s.back();
                s.pop_back();
                rst.push_back(top->val);
                if(top->left){
                    s.push_back(top->left);
                }
                if(top->right){
                    s.push_back(top->right);
                }
            }
            reverse(rst.begin(), rst.end());
            return rst;
        }

    };

	TEST_CASE("tests"){

        Solution testObj;
        TreeNode root{5}, left{1}, right{6};
        root.left = &left;
        root.right = &right;
		SECTION("sample"){
            auto rst = testObj.postorderTraversal(&root);
            vector<int> expected{1, 6, 5};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
		}
	}
}


