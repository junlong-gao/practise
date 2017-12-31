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
        TreeNode* helper(TreeNode* root){
            if(root == NULL) return NULL;
            if(root->left == NULL && root->right == NULL) return root;
            TreeNode* ret = NULL, *tail = NULL;
            if(root->right){
                ret = helper(root->right);
            }
            if(root->left){
                tail = helper(root->left);
            }
            if(tail) tail->right = root->right;
            if(root->left) root->right = root->left;
            root->left = NULL;
            return ret?ret:tail;
        }
    public:
        void flatten(TreeNode* root) {
            helper(root);            
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


