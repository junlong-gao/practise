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
    TreeNode *solve(const vector<int> &token, int &idx, int l, int r) {
        if (idx == token.size()) return nullptr;
        if (token[idx] <= l || token[idx] >= r) return nullptr;
        TreeNode *ret = new TreeNode(token[idx]);
        idx++;
        ret->left = solve(token, idx, l, ret->val);
        ret->right = solve(token, idx, ret->val, r);
        return ret;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int tmp = 0;
        return solve(preorder, tmp, INT_MIN, INT_MAX);
    }
};