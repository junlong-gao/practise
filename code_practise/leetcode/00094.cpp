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
public:
    vector<int> inorderTraversal(TreeNode* root) {
        TreeNode *cur = root;
        vector<TreeNode *> s;
        vector<int> ret;
        while (true) {
            while (cur) {
                s.push_back(cur);
                cur = cur->left;
            }
            if (s.empty()) {
                break;
            }
            cur = s.back(); s.pop_back();

            ret.push_back(cur->val);

            cur = cur->right;
        }

        return ret;
    }
};