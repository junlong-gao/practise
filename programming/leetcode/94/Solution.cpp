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
        vector<int> inorderTraversal(TreeNode* root) {
            vector<int> rst;
            vector<TreeNode*> s;
            while(root){
                s.push_back(root);
                root = root->left;
            }
            while(!s.empty()){
                auto top = s.back();
                rst.push_back(s.back()->val);
                s.pop_back();
                top = top->right;
                while(top){
                    s.push_back(top);
                    top = top->left;
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
            auto rst = testObj.inorderTraversal(&root);
            vector<int> expected{1,5,6};
            for(int i = 0; i < rst.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
        }
	}
}


