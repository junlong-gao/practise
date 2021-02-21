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
        TreeNode* down_search(TreeNode* root, TreeNode *p){
            TreeNode* iter = root;
            vector<TreeNode*> nodes;
            while(iter){
                nodes.push_back(iter);
                if(iter->val > p->val) iter = iter->left;
                if(iter->val < p->val) iter = iter->right;
                if(iter->val == p->val) break;
            }
            while(!nodes.empty()){
                if(nodes.back()->val > p->val) return nodes.back();
                nodes.pop_back();
            }
            return NULL;
        }
        TreeNode* min(TreeNode* root){
            TreeNode*  p =root;
            while(root){
                p = root;
                root = root->left;
                
            }
            return p;
        }
    public:
        TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
            if(p->right != NULL) return min(p->right);
            return down_search(root, p);
        }
    };
    
    TEST_CASE("tests"){
        TreeNode root{10};
        TreeNode left{5};
        TreeNode right{15};
        root.left = &left;
        root.right = &right;
		Solution testObj;
		SECTION("sample"){
            REQUIRE(testObj.inorderSuccessor(&root, &left) == &root);
            REQUIRE(testObj.inorderSuccessor(&root, &root) == &right);
            REQUIRE(testObj.inorderSuccessor(&root, &right) == NULL);
		}
        SECTION("min"){
            TreeNode ll{3};
            TreeNode lll{1};
            TreeNode llr{4};
            
            left.left = &ll;
            ll.left = &lll;
            ll.right = &llr;
            REQUIRE(testObj.inorderSuccessor(&root, &llr) == &left);
        }
	}
}


