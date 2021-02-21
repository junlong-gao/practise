/*
 * @lc app=leetcode id=698 lang=cpp
 *
 * [698] Partition to K Equal Sum Subsets
 *
 * https://leetcode.com/problems/partition-to-k-equal-sum-subsets/description/
 *
 * algorithms
 * Medium (44.30%)
 * Likes:    1207
 * Dislikes: 68
 * Total Accepted:    63.8K
 * Total Submissions: 143.9K
 * Testcase Example:  '[4,3,2,3,5,2,1]\n4'
 *
 * Given an array of integers nums and a positive integer k, find whether it's
 * possible to divide this array into k non-empty subsets whose sums are all
 * equal.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
 * Output: True
 * Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3),
 * (2,3) with equal sums.
 * 
 * 
 * 
 * 
 * Note:
 * 
 * 
 * 1 <= k <= len(nums) <= 16.
 * 0 < nums[i] < 10000.
 * 
 * 
 */

// @lc code=start
class Solution {
   /*
    */
   int target = 0;

   bool dfs(vector<int>& nums, int used, int curSum, int k) {
      if (k == 0) return used == (1 << nums.size()) - 1;

      for (int i = 0; i < nums.size(); ++i) {
         if (used & (1 << i)) continue;
         int newSum = curSum + nums[i];

         if (newSum > target) break;
         else if (newSum == target) {
            if (dfs(nums, used | (1 << i), 0, k - 1)) {
               return true;
            }
         } else {
            if (dfs(nums, used | (1 << i), newSum, k)) {
               return true;
            }
         }
      }

      return false;
   }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        if (nums.empty()) return k == 0;
        if (nums.size() < k) return false;

        int s = 0;
        for (auto e : nums) {
           s += e;
        }
        if (s % k) return false;

        target = s / k;
        sort(nums.rbegin(), nums.rend());
        return dfs(nums, 0, 0, k);
    }
};
// @lc code=end
