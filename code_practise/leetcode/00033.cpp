class Solution {
    /*
    - discuss cases by comparing nums[lo] and nums[mid], value range
      is straightforward
    - use [lo, hi), and make sure loop will find value if target exists, and
      terminate when it is empty set and return -1
    - to make sure loop will find value, check both values of lo and mid.
    */
public:
    int search(vector<int>& nums, int target) {
        int lo = 0; int hi = nums.size();
        while (hi - lo > 0) {
            int mid = lo + (hi - lo) / 2;
            if (target == nums[mid]) {
                return mid;
            }
            if (target == nums[lo]) {
                return lo;
            }
            if (nums[lo] >= nums[mid]) {
               if (target > nums[mid] && target < nums[lo]) {
                   lo = mid + 1;
               } else {
                   hi = mid;
               }
            } else {
                if (target > nums[lo] && target < nums[mid]) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
                
            }
        }
        return -1;
    }
};