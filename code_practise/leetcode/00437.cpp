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
    void search(int target,
                int prefix,
               int &ret,
               unordered_map<int, int> &bt,
               TreeNode *root) {
        if (root == nullptr) {
            return;
        }
        
        prefix += root->val;        
        ret += bt[prefix - target];
        
        bt[prefix] += 1;
        search(target, prefix, ret, bt, root->left);
        search(target, prefix, ret, bt, root->right);
        bt[prefix] -= 1; // (*)
    }
public:
    int pathSum(TreeNode* root, int sum) {
        unordered_map<int, int> bt;
        bt[0] = 1;
        int ret = 0;
        search(sum, 0, ret, bt, root);
        return ret;
    }
};