int x = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return 0;
}();


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
    
    int gid = 0;
    unordered_map<int, unordered_map<int, unordered_map<int, int>>> m;
    unordered_map<int, vector<TreeNode*>> ll;
    int tag(TreeNode *root) {
        if (root == nullptr) {
            ll[0].push_back(root);
            return 0;
        }
        int lid = tag(root->left);
        int rid = tag(root->right);
        if (m.count(root->val) == 0 || 
            m[root->val].count(lid) == 0 ||
            m[root->val][lid].count(rid) == 0) {
            m[root->val][lid][rid] = ++gid;
        } 
        
        ll[m[root->val][lid][rid]].push_back(root);
        return m[root->val][lid][rid];
    }
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
       tag(root);
        vector<TreeNode*> ret;
        for (auto &pr : ll) {
            if (pr.first == 0) continue;
            if (pr.second.size() == 1) continue;
            ret.push_back(pr.second.front());
        }
        return ret;
    }
};
