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
	int best = 0;
	unordered_map<TreeNode*, int> dec, inc;
	int longestPathDec(TreeNode* root) {
		if (root == nullptr) return 0;
		int l = longestPathDec(root->left);
		int r = longestPathDec(root->right);
		int ret = 1;
		if (root->left && root->val - root->left->val == 1) {
			ret = max(ret, 1 + l);
		}
		if (root->right && root->val - root->right->val == 1) {
			ret = max(ret, 1 + r);
		}
		
		dec[root] = ret;
		return ret;
	}
	int longestPathInc(TreeNode* root) {
		if (root == nullptr) return 0;
		int l = longestPathInc(root->left);
		int r = longestPathInc(root->right);
		int ret = 1;
		if (root->left && root->val - root->left->val == -1) {
			ret = max(ret, 1 + l);
		}
		if (root->right && root->val - root->right->val == -1) {
			ret = max(ret, 1 + r);
		}
		
		inc[root] = ret;
		return ret;
	}
	void findBest(TreeNode* root) {
		if (root == nullptr) return;
		best = std::max(best, inc[root] + dec[root] - 1);
		findBest(root->left);
		findBest(root->right);
	}
public:
    int longestConsecutive(TreeNode* root) {
        	longestPathDec(root);
	longestPathInc(root);
	findBest(root);
	return best;
    }
};

/*
tree recursion
*/
