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
    TreeNode* ctor(vector<int>& preorder,
                   int& head,
                   int lo,
                   int hi) {
        if (head == preorder.size()) return nullptr;
        if (preorder[head] > hi || preorder[head] < lo) return nullptr;
        TreeNode* root = new TreeNode(preorder[head]);
        head++;
        root->left = ctor(preorder, head, lo, root->val);
        root->right = ctor(preorder, head, root->val, hi);
        return root;
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int head = 0;
        return ctor(preorder, head, INT_MIN, INT_MAX);
    }
};
