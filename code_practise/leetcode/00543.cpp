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
	int best;
	int path(TreeNode* root) {
		if (root == nullptr) return 0;
		int lp = path(root->left) + (root->left ? 1 : 0);
		int rp = path(root->right) + (root->right ? 1 : 0);
		int ret = max(lp, rp);
		best = max(lp + rp, best);
		return ret;
	}
public:
    int diameterOfBinaryTree(TreeNode* root) {
        path(root);
	return best;
    }
};

