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
        vector<int> preorderTraversal(TreeNode* root) {
            vector<int> rst;
            vector<TreeNode*> s;
            s.push_back(root);
            while(!s.empty()){
                auto top = s.back();
                s.pop_back();
                rst.push_back(top->val);
                if(top->right){
                    s.push_back(top->right);
                }
                if(top->left){
                    s.push_back(top->left);
                }
            }
            return rst;
        }
	};
	TEST_CASE("tests"){
        Solution testObj;
        TreeNode root{5}, left{1}, right{6};
        root.left = &left;
        root.right = &right;
        SECTION("sample"){
            vector<int> expected{5,1,6};
            auto rst = testObj.preorderTraversal(&root);
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
        }
	}
}


