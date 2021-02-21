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
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> vals;
        auto visit = [&](TreeNode *r) {
            if (vals.count(k - r->val)) {
                return true;
            }
            vals.insert(r->val);
            return false;
        };
        
        // caller frees the nodes, and be sure to revert back the tree
        // before returning.
        bool ret = false; 
        while (root) {
            if (root->left) {
                TreeNode * cur = root->left;
                while (cur->right && cur->right != root) {
                    cur = cur->right;
                }
                if (cur->right == root) {
                    // the entire left subtree is done
                    cur->right = nullptr;
                    if (visit(root)) {
                        ret = true;
                    }
                    root = root->right;
                } else {
                    cur->right = root;
                    root = root->left;
                }
            } else {
                if (visit(root)) {
                    ret = true;
                }
                root = root->right;
            }
        }
        return ret;
    }
};