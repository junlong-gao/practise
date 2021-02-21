/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    struct ret_t {
        int n;
        int w;
    };
    
    double maxVal;
    
    ret_t search(TreeNode *root) {
        if (root == nullptr) {
            return ret_t{0, 0};
        }
        
        ret_t l = search(root->left);
        ret_t r = search(root->right);
        
        ret_t ret;
        ret.n = 1 + l.n + r.n;
        ret.w = root->val + l.w + r.w;
        
        maxVal = max(maxVal, (double)ret.w / (double)ret.n);
        
        return ret;
    }
public:
    double maximumAverageSubtree(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        
        search(root);
        return maxVal;
    }
};