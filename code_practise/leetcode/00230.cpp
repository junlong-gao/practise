#include <cstdlib>
#include <unordered_map>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    /*
    int helper(TreeNode* root){
        if(root == NULL) return 0;
        return helper(root->left) + helper(root->right) + 1;
    }

    int finder(TreeNode* root, int k){
        int count = helper(root->left);
        if(count >= k) return finder(root->left, k);
        if(count < k - 1) return finder(root->right, k - (count + 1));
        return root->val;
    }
     */
public:
    int kthSmallest(TreeNode* root, int k) {
        vector<TreeNode*> s;
        while(root!=NULL){
            s.push_back(root);
            root = root->left;
        }
        while(!s.empty()){
            auto cur = s.back();
            s.pop_back();
            k--;
            if(k==0) return cur->val;
            auto left = cur->right;
            while(left != NULL){
                s.push_back(left);
                left = left->left;
            }
        }
        return -1;
    }
};