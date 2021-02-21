/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
longest path from root t
if left is not empty and left.v = t.v then max(t.cur, longest path from root left.v)
if right is not empty and right.v = t.v then max(t.cur, longest path from root right.v)
best = max(best, t.cur)
*/

class Solution {
	int best = 0;
	int helper(TreeNode * root) {
		if (root == nullptr) return 0;
		int left = helper(root->left);
		int right = helper(root->right);
		int cur = 0; int connect = 0;
		if (root->left && root->left->val == root->val) {
/*
XXX1
			cur = max(cur, left) + 1; connect += left + 1;
*/
cur = max(cur, left + 1); connect += left + 1;
		}

		if (root->right && root->right->val == root->val) {
/*
XXX1
			cur = max(cur, right) + 1; connect += right + 1;
*/
			cur = max(cur, right + 1); connect += right + 1;
		}

		best = max(best, connect);
		return cur;
	}
public:
   int longestUnivaluePath(TreeNode* root) {
	helper(root);
	return best;
   }
};

/*
1
4		6
4		4 6	          6

compile error:
emplace back take direct ctor param!

wa:
fail to under stand the problem: a path no need to be single direction
XXX1
*/
