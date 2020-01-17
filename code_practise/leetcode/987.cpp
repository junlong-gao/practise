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
    struct point {
        TreeNode *r;
        int X, Y;
    };
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        deque<point> q{point{root, 0, 0}};
        map<int, map<int, set<int>>> g;
        g[0][0] = {root->val};
        while (q.size()) {
            auto top = q.front(); q.pop_front();
            if (top.r->left) {
                g[top.X - 1][top.Y + 1].insert(top.r->left->val);
                q.push_back(point{top.r->left, top.X-1, top.Y + 1});
            }
            if (top.r->right) {
                g[top.X + 1][top.Y + 1].insert(top.r->right->val);
                //cout << top.X + 1 << " " << top.Y + 1 << " " << top.r->right->val << endl;
                q.push_back(point{top.r->right, top.X + 1, top.Y + 1});
            }
        }
        vector<vector<int>> ret;
        for (auto pr : g) {
            ret.emplace_back();
            for (auto pr2 : pr.second) {
                for (auto v : pr2.second) {
                    ret.back().push_back(v);
                }
            }
        }
        
        return ret;
    }
};