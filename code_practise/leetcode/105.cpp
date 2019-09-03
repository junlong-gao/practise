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
    unordered_map<int, int> root_idx;
    pair<TreeNode*, int> helper(int pre_idx, int i, int j,
                    vector<int>& pre, vector<int>& in) {
        if (i == j) return make_pair(nullptr, pre_idx);
        TreeNode* r = new TreeNode(pre[pre_idx]);
        int in_r = root_idx[pre[pre_idx]];
        auto retl = helper(pre_idx + 1, i, in_r, pre, in);
        
        r->left = retl.first;
        pre_idx = retl.second;
        
        auto retr = helper(pre_idx, in_r + 1, j, pre, in);
        r->right = retr.first;
        pre_idx = retr.second;
        
        return make_pair(r, pre_idx);
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); ++i) {
            root_idx[inorder[i]] = i;
        }
        
        auto ret = helper(0, 0, preorder.size(), preorder, inorder);
        return ret.first;
    }
};
