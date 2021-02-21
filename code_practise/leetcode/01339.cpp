/*
 1339. Maximum Product of Splitted Binary Tree
*/
class Solution {
    unordered_map<TreeNode*, int> s;
    int subTreeSum(TreeNode *r) {
        if (r == nullptr) {
            s[r] = 0;
            return 0;
        }
        int ls = subTreeSum(r->left);
        int rs = subTreeSum(r->right);
        s[r] = r->val + ls + rs;
        return s[r];
    }

    long long rootSum = 0;
    long long best = 0;
    long long M = 1e9 + 7;

    void dfs(TreeNode *r) {
        if (r == nullptr) {
            return;
        }
        best = max(best, s[r->left] * (rootSum - s[r->left]));
        best = max(best, s[r->right] * (rootSum - s[r->right]));
        dfs(r->left);
        dfs(r->right);
        return;
    }
public:
    int maxProduct(TreeNode* root) {
        rootSum = subTreeSum(root);
        dfs(root);
        return best % M;
    }
};