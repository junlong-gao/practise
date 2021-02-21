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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root==nullptr) return {};
        vector<vector<int>> ret;
        deque<TreeNode* > q{root};
        while(q.size()) {
            int s = q.size();
            ret.push_back({});
            for (int i = 0; i < s; ++i) {
                if (q.front()->left) {
                    q.push_back(q.front()->left);
                }
                if (q.front()->right) {
                    q.push_back(q.front()->right);
                }
                ret.back().push_back(q.front()->val);
                q.pop_front();
            }
        }
        
        return ret;
    }
};
