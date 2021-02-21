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
    bool valid;
    int min;
    int max;
};
    ret_t isValid_(TreeNode *root) {
        if (root == nullptr) return ret_t {true, 0, 0};
        auto ltree = isValid_(root->left);
        if (!ltree.valid || (root->left && ltree.max >= root->val)) {
            return ret_t {false, 0, 0};
        }
        auto rtree = isValid_(root->right);
        if (!rtree.valid || (root->right && rtree.min <= root->val)) {
            return ret_t {false, 0, 0};
        }
        return ret_t {true, root->left ? ltree.min : root->val, root->right ? rtree.max : root->val};
    }
public:
    bool isValidBST(TreeNode* root) {
        return isValid_(root).valid;
    }
};
