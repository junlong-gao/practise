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
  int getMinimumDifference(TreeNode *root) {
    TreeNode *cur = root;
    int prev = INT_MAX;
    int best = INT_MAX;
    while (cur) {
      if (cur->left == nullptr) {
        if (prev != INT_MAX) {
          assert(cur->val >= prev);
          best = min(best, cur->val - prev);
        }
        prev = cur->val;
        cur = cur->right;
      } else {
        TreeNode *pred = cur->left;
        while (pred->right && pred->right != cur) {
          pred = pred->right;
        }
        if (pred->right == nullptr) {
          pred->right = cur;
          cur = cur->left;
        } else {
          pred->right = nullptr;
          if (prev != INT_MAX) {
            assert(cur->val >= prev);
            best = min(best, cur->val - prev);
          }
          prev = cur->val;
          cur = cur->right;
        }
      }
    }
    return best;
  }
};
