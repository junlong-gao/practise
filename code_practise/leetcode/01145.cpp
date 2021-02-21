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
    TreeNode *px = nullptr;
    int x_;
    unordered_map<TreeNode*, int> nodes;
    int counter(TreeNode* v) {
        if (v == nullptr) {
            return 0;
        }
        int& ret = nodes[v];
        ret = counter(v->left) + counter(v->right) + 1;      
        if (v->val == x_) {
            px = v;
        }
        
        return ret;
    }
public:
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        x_ = x; 
        
        int ret = counter(root);
        //assert(ret == n);
        
        vector<int> c;
        c.push_back(max(n - nodes[px], 0));
        c.push_back(nodes[px->left]);
        c.push_back(nodes[px->right]);
        sort(c.begin(), c.end());
        return c[2] > 1 + c[1] + c[0];
    }
};
