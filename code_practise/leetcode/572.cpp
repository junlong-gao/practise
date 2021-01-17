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
    size_t search(TreeNode *r, unordered_set<size_t> *fp) {
        if (r == nullptr) {
            if (fp) {
                fp->insert(hash<string>{}(""));
            }
            return hash<string>{}("");
        }
        
        size_t ret = hash<string>{}(to_string(search(r->left, fp)) + to_string(r->val) + to_string(search(r->right, fp)));
        if (fp) {
            fp->insert(ret);
        }
        return ret;
    }
    
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        unordered_set<size_t> fp;
        search(s, &fp);
        return fp.count(search(t, nullptr));
        
    }
};