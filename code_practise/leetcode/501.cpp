static auto x = [](){
    // turn off sync
    std::ios::sync_with_stdio(false);
    // untie in/out streams
    cin.tie(NULL);
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
    int curVal = INT_MIN;
    int curCount = 0;
    int curBest = 0;
    vector<int> bestMode;
    void visit(int n) {
        if (curVal != n) {
            curVal = n;
            curCount = 0;
        } else {
            curCount++;
        }
        
        if (curCount > curBest) {
            curBest = curCount;
            bestMode.clear();
            bestMode.push_back(n);
        } else if (curCount == curBest) {
            if (bestMode.empty() || bestMode.back() != n) {
                bestMode.push_back(n);
            }
        }
    }
public:
    vector<int> findMode(TreeNode* root) {
        while(root) {
            if (!root->left) {
                visit(root->val);
                root = root->right;
            } else {
                TreeNode *cur = root->left;
                while(cur->right && cur->right != root) {
                    cur = cur->right;
                }
                
                if (cur->right == nullptr) {
                    cur->right = root;
                    root = root->left;
                } else {
                    cur->right = nullptr;
                    visit(root->val);
                    root = root->right;
                }
            }
        }
        return bestMode;
    }
};
