class Solution {
struct ret_t {
    TreeNode *r;
    int size;
};
    unordered_map<int, int> root_idx;
    ret_t helper(int pre_idx, int i, int j,
                    vector<int>& pre, vector<int>& in) {
        if (i == j) return ret_t{nullptr, 0};
        TreeNode* r = new TreeNode(pre[pre_idx]);
        int in_r = root_idx[pre[pre_idx]];
        
        auto ltree = helper(pre_idx + 1, i, in_r, pre, in);
        r->left = ltree.r;
        
        auto rtree = helper(pre_idx + 1 + ltree.size, in_r + 1, j, pre, in);
        r->right = rtree.r;
        
        return ret_t {r, ltree.size + 1 + rtree.size};
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); ++i) {
            root_idx[inorder[i]] = i;
        }
        
        return helper(0, 0, preorder.size(), preorder, inorder).r;
    }
};
