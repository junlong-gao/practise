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
/*
Invariant:
path represents the root->node path of the node currently pointing to, and the special case
when it is one before the first value (on init).

Next() and Prev() just use the path to do tree traversal to find the next/prev node.

HasNext() and HasPrev() will simulate a traversal once, and remember the left most/right most
tree node on subsequent calls (cache, mutable if use const modifier).

Everything is amortized O(1), since total cost of each op is linear to the number of the tree node,
Average O(logn) as it is BST.
*/
class BSTIterator {
    vector<TreeNode*> path;
    TreeNode *root, *lmost {nullptr}, *rmost {nullptr};
    void refill() {
        TreeNode *cur = root;
        while (cur) {
            path.push_back(cur);
            cur = cur->left;
        }
    }
public:
    BSTIterator(TreeNode* root) {
        this->root = root;
    }
    
    bool hasNext() {
        if (path.empty()) {
            return root != nullptr;
        }
        
        if (rmost != nullptr) {
            return path.back() != rmost;
            
        }
        
        TreeNode *cur = path.back();
        if (cur->right) {
            return true;
        } else {
            for (int i = path.size() - 1; i > 0; i--) {
                if (path[i] == path[i - 1]->left) {
                    return true;
                }
            }
            rmost = path.back();
            return false;
        }
    }
    
    int next() {
        if (path.empty()) {
            refill();
            return path.back()->val;
        }
        TreeNode *cur = path.back();
        if (cur->right) {
            path.push_back(cur->right);
            while (path.back()->left) {
                path.push_back(path.back()->left);
            }
        } else {
            path.pop_back();
            while (path.size() && cur == path.back()->right) {
                cur = path.back();
                path.pop_back();
            }
        }
        return path.back()->val;
    }
    
    bool hasPrev() {
        if (path.empty()) {
            return false;
        }
        
        if (lmost != nullptr) {
            return path.back() != lmost;
        }
        
        TreeNode *cur = path.back();
        if (cur->left) {
            return true;
        } else {
            for (int i = path.size() - 1; i > 0; i--) {
                if (path[i] == path[i - 1]->right) {
                    return true;
                }
            }
            lmost = path.back();
            return false;
        }
    }
    
    int prev() {
        if (path.empty()) {
            assert(0);
        }
        TreeNode *cur = path.back();
        if (cur->left) {
            path.push_back(cur->left);
            while (path.back()->right) {
                path.push_back(path.back()->right);
            }
        } else {
            path.pop_back();
            while (path.size() && cur == path.back()->left) {
                cur = path.back();
                path.pop_back();
            }
        }
        return path.back()->val;
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * bool param_1 = obj->hasNext();
 * int param_2 = obj->next();
 * bool param_3 = obj->hasPrev();
 * int param_4 = obj->prev();
 */
