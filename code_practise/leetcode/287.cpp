class Solution {
public:
    /*
     * Floyd loop detection.
     * Consider num as a function from [0, n] -> [1, n].
     * Condider sequence resulting from applying function num:
     * x_0 = 0;
     * x_1 = num[x_0];
     * x_2 = num[x_1];
     * ...
     *
     * There must be a first x_k repeated (= x_l for some l < k).
     *
     * Let slow = 0; fast = 0; slow' = num[slow]; fast' = num[num[fast]]
     * Let d_slow = # of applying function num to get the current slow
     * Let t = # of applying function num to get repeatition after x_l
     * Let l = # of applying function num to reach x_l
     * Let delta = # of applying function num to reach slow == fast after 
     * slow has passed l.
     * Then d_fast - d_slow = m * t for some m > 0
     * Since d_fast = 2 * d_slow, => d_slow = m * t
     * Also, d_slow = l + delta, so l = m * t - delta.
     *
     * Therefore, in order to find l, we need to start walking from 0, applying
     * num for m * t - delta times. On the other hand, if we apply num m * t - delta
     * times from slow, we end up at l (consider modular -delta).
     * So start with 0 we start another fast, and let slow walk at the same speed
     * as fast until they meet. Then it is the l we seek.
     */
    int findDuplicate(vector<int>& nums) {
       int slow = 0;
       int fast = 0;

       while (true) {
          slow = nums[slow];
          fast = nums[nums[fast]];

          if (slow == fast) {
             break;
          }
       }

       fast = 0;
       while(fast != slow) {
          slow = nums[slow];
          fast = nums[fast];
       }

       return slow;
    }

    /*
     * Standard binary search.
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
