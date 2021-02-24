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
    unordered_map<int, unordered_map<int, unordered_map<int, int>>> treeMap; // (val, id1, id2) -> id
    int id {1};
    int getId(TreeNode *root, unordered_set<int> *output) {
        if (root == nullptr) {
            return 0;
        }
        int leftId = getId(root->left, output);
        int rightId = getId(root->right, output);
        int gotId = treeMap[root->val][leftId][rightId];
        if (gotId == 0) {
            gotId = id++;
            treeMap[root->val][leftId][rightId] = gotId;
        }
        if (output) {
            output->insert(gotId);
        }
        return gotId;
    }
    
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        int target = getId(t, nullptr);
        unordered_set<int> trees;
        getId(s, &trees);
        return trees.count(target) > 0;
    }
};