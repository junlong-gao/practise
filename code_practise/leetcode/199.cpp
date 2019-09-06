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
    vector<int> rightSideView(TreeNode* root) {
        if (root == nullptr) return {};
        vector<int> ret;
        deque<TreeNode*> q;
        q.push_back(root);
        while (q.size()) {
            ret.push_back(q.back()->val);
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                if (q.front()->left) {
                    q.push_back(q.front()->left);
                }
                if (q.front()->right) {
                    q.push_back(q.front()->right);
                }
                q.pop_front();
            }
        }
        
        return ret;
    }
};
