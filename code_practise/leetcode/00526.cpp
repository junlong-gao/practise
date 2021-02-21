/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 *
 * BNF:
 * tree -> num { push num } tree
 *       | (tree) { link back to the second back left; pop }
 *       | (tree) { link back to the second back left; pop } (tree) { ... right ... }
 *       | eps
 *
 * num -> digit* { push num }
 *      | -num { push -num }
 */
class Solution {
    vector<TreeNode*> ss;
    string in;
    int lh = 0;
    void num() {
        int sign = 1;
        if (in[lh] == '-') { sign = -1; lh++; }

        int cur = lh;
        while (lh < in.length() && isdigit(in[lh])) { lh++; }
        ss.push_back(new TreeNode(sign * stoi(in.substr(cur, lh - cur))));
    }
    void tree () {
        if (lh == in.length()) return; // eps production
        if (in[lh] == '-' || isdigit(in[lh])) {
            num();
            tree();
        } else if (in[lh] == '(') {
            lh++; // (
            tree();
            assert(in[lh == ')']); lh++;

            assert(ss.size() >= 2);
            TreeNode *lc = ss.back(); ss.pop_back();
            ss.back()->left = lc;

            if (lh == in.length() || in[lh] != '(') return;
            lh++; // (
            tree();
            assert(in[lh == ')']); lh++; // )

            assert(ss.size() >= 2);
            TreeNode *rc = ss.back(); ss.pop_back();
            ss.back()->right = rc;
        } else {
            //eps production : )
        }
    }
public:
    TreeNode* str2tree(string s) {
        swap(s, in);
        tree();
        return ss.empty() ? nullptr : ss.back();
    }
};
