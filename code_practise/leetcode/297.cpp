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
    const char TERM = 'N';
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
       if (root == nullptr) {
           return string{TERM};
       }
       string ret = to_string(root->val) + " " + serialize(root->left) + " " + serialize(root->right);
        return ret;
    }

    TreeNode *deserialize_(const string &data, int &idx) {
        if (idx == data.size()) {
            return nullptr;
        }
        if (data[idx] == TERM) {
            TreeNode *ret = nullptr;
            idx += 2; // term and whitespace
            return ret;
        } else {
            int tmp = idx;
            while (idx < data.size() && data[idx] != ' ') {
                idx++;
            }
            if (idx < data.size()) {idx++;}
            TreeNode *ret = new TreeNode(stoi(data.substr(tmp, idx - tmp)));
            ret->left = deserialize_(data, idx);
            ret->right = deserialize_(data, idx);
            return ret;
        }
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int idx = 0;
        return deserialize_(data, idx);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));