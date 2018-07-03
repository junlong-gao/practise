/*
 * [33] Search in Rotated Sorted Array
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array/description/
 *
 * algorithms
 * Medium (31.96%)
 * Total Accepted:    271.8K
 * Total Submissions: 850.5K
 * Testcase Example:  '[4,5,6,7,0,1,2]\n0'
 *
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 * 
 * (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 * 
 * You are given a target value to search. If found in the array return its
 * index, otherwise return -1.
 * 
 * You may assume no duplicate exists in the array.
 * 
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 * 
 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        if (nums.size() == 1) return target == nums.front() ? 0 : -1;
        if (target == nums.front()) return 0;

        auto check = [&](int val) {
           assert(val != nums.front());
           int sign = (target - nums.front()) * (val - nums.front());
           if (sign >= 0) {
              // same side
              return val < target;
           } else {
              // different side
              if (target > nums.front()) {
                 // [p, target, val]
                 // ==> [p, target, +INF]
                 return false;
              } else {
                 // [p, val, target]
                 // [p, -INF, target]
                 return true;
              }
           }
        };

        int lo = 0, hi = nums.size() - 1;
        // (lo, hi]
        while (hi - lo > 1) {
           int mid = lo + (hi - lo) / 2;
           int midVal = nums[mid];
           if (check(midVal)) {
              lo = mid;
           } else {
              hi = mid;
           }
        }
        return nums[hi] == target ? hi : -1;
    }
};
