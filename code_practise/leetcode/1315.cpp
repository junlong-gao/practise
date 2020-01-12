/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    int ret = 0;
    void dfs(TreeNode* cur, int p, int gp) {
        if (cur == nullptr) return;
        if (gp % 2 == 0) ret += cur->val;
        dfs(cur->left, cur->val, p);
        dfs(cur->right, cur->val, p);
    }
public:
    int sumEvenGrandparent(TreeNode* root) {
        dfs(root, 1,  1);
        return ret;
    }
};