/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) return "";
        return to_string(root->val) + " " + serialize(root->left) + " " + serialize(root->right);
    }

    TreeNode* helper(vector<int>& pre,
                     int& head,
                     int lo,
                     int hi) {
        if (head == pre.size() || pre[head] < lo || pre[head] > hi) {
            return nullptr;
        }
        
        auto* root = new TreeNode(pre[head]);
        head++;
        root->left = helper(pre, head, lo, root->val);
        root->right = helper(pre, head, root->val, hi);
        return root;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<int> parsed;
        auto r = istringstream(data);
        copy(istream_iterator<int>(r), std::istream_iterator<int>(), back_inserter(parsed));
        int head = 0;
        return helper(parsed, head, INT_MIN, INT_MAX);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
