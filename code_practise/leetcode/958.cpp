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
public:
    bool isCompleteTree(TreeNode* root) {
        unordered_map<TreeNode*, long long> mp;
        mp[root] = 1;
        deque<TreeNode* > level;
        level.push_back(root);
        int sofar = 1;
        //cout << "---" << endl;
        while (level.size()) {
            int n = level.size();
            for (int i = 0; i < n; ++i) {
                //cout << level.front() << endl;
                if (level.front()->left) {
                    sofar++;
                    if (sofar != mp[level.front()] * 2) return false;
                    mp[level.front()->left] = mp[level.front()] * 2;
                    level.push_back(level.front()->left);
                }
                if (level.front()->right) {
                    sofar++;
                    if (sofar != mp[level.front()] * 2 + 1) return false;
                    mp[level.front()->right] = mp[level.front()] * 2 + 1;
                    level.push_back(level.front()->right);
                }
                level.pop_front();
            }
        }
        
        return true;
    }
};
