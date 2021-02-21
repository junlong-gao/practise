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
    void createGraph(TreeNode *r, unordered_map<TreeNode *, vector<TreeNode *>> &g) {
        if (r == nullptr) return;
        if (r->left) {
            g[r].push_back(r->left);
            g[r->left].push_back(r);
            createGraph(r->left, g);
        }
        if (r->right) {
            g[r].push_back(r->right);
            g[r->right].push_back(r);
            createGraph(r->right, g);
        }
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        unordered_map<TreeNode *, vector<TreeNode *>> g;
        createGraph(root, g);
        
        deque<TreeNode *> q;
        set<TreeNode *> visited;
        int d = 0;
        
        visited.insert(target);
        q.push_back(target);
        while (q.size()) {
            if (d == K) {
                vector<int> ret;
                for (auto v : q) {
                    ret.push_back(v->val);
                }
                return ret;
            } else {
                d++;
                int sz = q.size();
                for (int i = 0; i < sz; ++i) {
                    TreeNode *top = q.front(); q.pop_front();
                    for (auto n : g[top]) {
                        if (visited.count(n)) {
                            continue;
                        }
                        
                        visited.insert(n);
                        q.push_back(n);
                    }
                }
            }
        }
        return {};
    }
};