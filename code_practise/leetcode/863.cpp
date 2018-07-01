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
    
    void ctor(TreeNode *root, unordered_map<int, vector<int>> &g) {
        if (root == nullptr) return;
        if (root->left) {
            g[root->val].push_back(root->left->val);
            g[root->left->val].push_back(root->val);
            ctor(root->left, g);
        }
        if (root->right) {
            g[root->val].push_back(root->right->val);
            g[root->right->val].push_back(root->val);
            ctor(root->right, g);
        }
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        unordered_map<int, vector<int>> g;
        ctor(root, g);
        
        vector<int> q; int d = 0;
        unordered_set<int> visited;
        
        visited.insert(target->val);
        q.emplace_back(target->val);
        while (q.size()) {
            if (d == K) {
                return q;
            }
            vector<int> tmp;
            for (auto node : q) {
                for (auto n : g[node]) {
                    //cout << n << " " << visited.count(n) << " " << visited.size() << endl;
                    if (visited.count(n) == 0) {
                        //cout << "p:"<<n<<endl;
                        tmp.push_back(n);
                        visited.insert(n);
                    }
                }
            }
            d++; 
            swap(tmp, q);   
        }
        return {};
    }
};
