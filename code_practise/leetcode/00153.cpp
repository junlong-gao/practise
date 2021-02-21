/*
 * [153] Find Minimum in Rotated Sorted Array
 *
 * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/
 *
 * algorithms
 * Medium (41.21%)
 * Total Accepted:    205.1K
 * Total Submissions: 497.7K
 * Testcase Example:  '[3,4,5,1,2]'
 *
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 * 
 * (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
 * 
 * Find the minimum element.
 * 
 * You may assume no duplicate exists in the array.
 * 
 * Example 1:
 * 
 * 
 * Input: [3,4,5,1,2] 
 * Output: 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: [4,5,6,7,0,1,2]
 * Output: 0
 * 
 * 
 */
class Solution {
public:
    int findMin(vector<int>& nums) {
       assert(nums.size());
       if (nums.size() == 1) return nums.front();
       int lo = -1, hi = nums.size() - 1;
       // (lo, hi]
       while (hi - lo > 1) {
          int mid = lo + (hi - lo) / 2;
          int p = nums.front();
          if (nums[mid] < p) {
             hi = mid;
          } else {
             lo = mid;
          }
       }
       return std::min(nums[0], nums[hi]);
    }
};
