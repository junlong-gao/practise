/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        bool ltoR = true;
        deque<TreeNode*> q{root};
        vector<vector<int>> ret;
        while (q.size()) {
            int n = q.size();
            ret.emplace_back();
            for (int i = 0; i < n; ++i) {
                auto top = q.front(); q.pop_front();
                ret.back().push_back(top->val);
                if (top->left) {
                    q.push_back(top->left);
                }
                if (top->right) {
                    q.push_back(top->right);
                }
            }
            if (!ltoR) {
                reverse(ret.back().begin(), ret.back().end());
            }
            ltoR = !ltoR;
        }
        return ret;
    }
};