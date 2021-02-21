class Solution {
public:
    /*
     * Floyd loop detection.
     * let fast be running 2x faster than slow, then when they meet in the loop, we know:
     * 1. by speed:
     * dfast = dslow * 2 => dfast - dslow = dslow
     * 2. because they meet in the loop:
     * dfast = dslow + loop length
     *
     * so we have dslow = loop length.
     * Since total length = non loop length + loop length, we know now slow stops at a
     * a position from the termination (loop point) of distance non loop length.
     *
     * Now there are 2 points of distance non loop length to the termination: begin
     * and slow, so let both begin and slow to move forward, they will arrive at the
     * terminal point.
     */
    int findDuplicate(vector<int>& nums) {
        int fast = nums[nums[nums[0]]];
        int slow = nums[nums[0]];
        while (fast != slow) {
            fast = nums[nums[fast]];
            slow = nums[slow];
        }
        
        int ret = nums[0];
        while (ret != slow) {
            ret = nums[ret];
            slow = nums[slow];
        }
        
        return ret;
    }
    /*
     * Standard binary search. This is also very cool.
     */
    int findDuplicate(vector<int>& nums) {
       int lo = 1, hi = nums.size();
       while (hi - lo > 1) {
          int mid = lo + (hi - lo) / 2;
          int count = 0;
          for (int i = 0; i < nums.size(); ++i) {
             if (nums[i] < mid) count++;
          }

          if (count > mid - 1) {
             hi = mid;
          } else {
             lo = mid;
          }
       }

       return lo;
    }
};


/*
TESTS
[1,1,2]
[2,1,1]
[2,2,1]
*/
