/*
 * @lc app=leetcode id=364 lang=cpp
 *
 * [364] Nested List Weight Sum II
 *
 * https://leetcode.com/problems/nested-list-weight-sum-ii/description/
 *
 * algorithms
 * Medium (60.64%)
 * Likes:    428
 * Dislikes: 104
 * Total Accepted:    50.6K
 * Total Submissions: 83.5K
 * Testcase Example:  '[[1,1],2,[1,1]]'
 *
 * Given a nested list of integers, return the sum of all integers in the list
 * weighted by their depth.
 * 
 * Each element is either an integer, or a list -- whose elements may also be
 * integers or other lists.
 * 
 * Different from the previous question where weight is increasing from root to
 * leaf, now the weight is defined from bottom up. i.e., the leaf level
 * integers have weight 1, and the root level integers have the largest
 * weight.
 * 
 * Example 1:
 * 
 * 
 * 
 * Input: [[1,1],2,[1,1]]
 * Output: 8 
 * Explanation: Four 1's at depth 1, one 2 at depth 2.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: [1,[4,[6]]]
 * Output: 17 
 * Explanation: One 1 at depth 3, one 4 at depth 2, and one 6 at depth 1; 1*3 +
 * 4*2 + 6*1 = 17.
 * 
 * 
 * 
 * 
 */

// @lc code=start
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
    unordered_map<int, int> levelSums;
    int height = 1;
    void dfs(const vector<NestedInteger>& nestedList, int d) {
       height = max(d, height);
       for (const auto& l : nestedList) {
          if (l.isInteger()) {
             levelSums[d] += l.getInteger();
          } else {
             dfs(l.getList(), d + 1);
          }
       }
    }
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
       dfs(nestedList, 1);
       int ret = 0;
       for (int h = 1; h <= height; ++h) {
          ret += (height + 1 - h) * levelSums[h];
       }

       return ret;
    }
};
// @lc code=end
