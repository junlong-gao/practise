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
  int idx = 0;
  TreeNode* helper(const string& S, int level) {
    for (int i = idx; i < idx + level; ++i) {
      if (i >= S.size()) return nullptr;
      if (S[i] != '-') return nullptr;
    }
    if (idx + level >= S.size() || !isdigit(S[idx + level])) {
      return nullptr;
    }
    idx += level;
    int cur = idx;
    while (idx < S.length() && isdigit(S[idx])) {
      idx++;
    }
    TreeNode* root = new TreeNode(stoi(S.substr(cur, idx - cur)));
    root->left = helper(S, level + 1);
    root->right = helper(S, level + 1);
    return root;
  }
public:
    TreeNode* recoverFromPreorder(string S) {
        return helper(S, 0);
    }
};
