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
public:
    int minDiffInBST(TreeNode* root) {
        int best = INT_MAX;
        int prev = best;
        auto update = [&](int val) {
            if (prev != INT_MAX) {
                best = min(val - prev, best);
            }
            prev = val;
        };
        while (root) {
            if (root->left == nullptr) {
                update(root->val);
                root = root->right;
            } else {
                TreeNode* t = root->left;
                while(t->right && t->right != root) {
                    t = t->right;
                }
                if (t->right == nullptr) {
                    t->right = root;
                    root = root->left;
                } else {
                    t->right = nullptr;
                    update(root->val);
                    root = root->right;
                }
            }
        }
        return best;
    }
};
