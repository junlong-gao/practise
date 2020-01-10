/*
 * @lc app=leetcode id=366 lang=cpp
 *
 * [366] Find Leaves of Binary Tree
 *
 * https://leetcode.com/problems/find-leaves-of-binary-tree/description/
 *
 * algorithms
 * Medium (68.67%)
 * Likes:    823
 * Dislikes: 11
 * Total Accepted:    59.1K
 * Total Submissions: 86.1K
 * Testcase Example:  '[1,2,3,4,5]'
 *
 * Given a binary tree, collect a tree's nodes as if you were doing this:
 * Collect and remove all leaves, repeat until the tree is empty.
 * 
 * 
 * 
 * Example:
 * 
 * 
 * Input: [1,2,3,4,5]
 * 
 * 1
 * ⁠        / \
 * ⁠       2   3
 * ⁠      / \     
 * ⁠     4   5    
 * 
 * Output: [[4,5,3],[2],[1]]
 * 
 * 
 * 
 * 
 * Explanation:
 * 
 * 1. Removing the leaves [4,5,3] would result in this tree:
 * 
 * 
 * ⁠         1
 * ⁠        / 
 * ⁠       2          
 * 
 * 
 * 
 * 
 * 2. Now removing the leaf [2] would result in this tree:
 * 
 * 
 * ⁠         1          
 * 
 * 
 * 
 * 
 * 3. Now removing the leaf [1] would result in the empty tree:
 * 
 * 
 * ⁠         []         
 * 
 */

// @lc code=start
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
    vector<vector<int>> findLeaves(TreeNode* root) {
       if (root == nullptr) {
          return {};
       }
       unordered_map<TreeNode*, TreeNode*> p;
       unordered_map<TreeNode*, int> d;
       deque<TreeNode*> leaf;
       vector<vector<int>> ret;

       deque<TreeNode*> q;
       q.push_back(root);
       while (q.size()) {
          auto top = q.front(); q.pop_front();
          if (top->left) {
             d[top]++;
             p[top->left] = top;
             q.push_back(top->left);
          }
          if (top->right) {
             d[top]++;
             p[top->right] = top;
             q.push_back(top->right);
          }

          if (d[top] == 0) {
             leaf.push_back(top);
          }
       }

       while (leaf.size()) {
          ret.emplace_back();
          int s = leaf.size();
          for (int i = 0; i < s; ++i) {
             ret.back().push_back(leaf.front()->val);
             d[p[leaf.front()]]--;
             if (d[p[leaf.front()]] == 0) {
                leaf.push_back(p[leaf.front()]);
             }
             leaf.pop_front();
          }
       }

       return ret;
    }
};
// @lc code=end
