#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>


namespace lee270{
    using namespace std;
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    class Solution {
        
    public:
        int closestValue(TreeNode* root, double target) {
            vector<TreeNode*> stack;
            while(root){
                stack.push_back(root);
                root = root->left;
            }
            double diff = -numeric_limits<double>::max();
            while(!stack.empty()){
                auto top = stack.back();
                stack.pop_back();
                double t = top->val - target;
                diff = abs(t) > abs(diff) ? diff : t;
                if(t >= 0){
                    return diff + target;
                }
                auto right = top->right;
                while(right){
                    stack.push_back(right);
                    right = right->left;
                }
            }
            return diff + target;
        }
    };
    TEST_CASE("lee270 smoke"){
        Solution testObj;
        SECTION("sample"){
            TreeNode root{5}, left{1}, right{6};
            root.left = &left;
            root.right = &right;
            REQUIRE(testObj.closestValue(&root, 0.9) == 1);
            
        }
	}
}


