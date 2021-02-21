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
        string ret = to_string(root->val) +
                        (root->left ? " " + serialize(root->left) : "") +
                        (root->right ? " " + serialize(root->right) : "");
        return ret;
    }

    TreeNode *solve(const string &data, int &idx, int l, int r) {
        if (idx == data.size()) {return nullptr;}

        int tmp = idx;
        while (idx < data.size() && data[idx] != ' ') {idx++;}
        if (idx < data.size()) {
            idx++;
        }

        int v = stoi(data.substr(tmp, idx - tmp));
        if (v <= l || v >= r) {
            idx = tmp; // unwind state
            return nullptr;
        }
        TreeNode *ret = new TreeNode(v);
        ret->left = solve(data, idx, l, v);
        ret->right = solve(data, idx, v, r);
        return ret;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int tmp = 0;
        return solve(data, tmp, INT_MIN, INT_MAX);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;