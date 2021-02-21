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
class BSTIterator {
    vector<TreeNode *> path;
public:
    BSTIterator(TreeNode* root) {
        while (root) {
            path.push_back(root);
            root = root->left;
        }
    }
    
    int next() {
        int ret = path.back()->val;
        TreeNode *cur = path.back()->right;
        
        path.pop_back();

        while (cur) {
            path.push_back(cur);
            cur = cur->left;
        }
        return ret;
    }
    
    bool hasNext() {
        return path.size() > 0;   
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
