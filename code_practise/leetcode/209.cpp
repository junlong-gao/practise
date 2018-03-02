/*
 * test> lc submit 209.cpp
 *   ✔ Accepted
 *   ✔ 15/15 cases passed (12 ms)
 *   ✔ Your runtime beats 34.97 % of cpp submissions
 */
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
       if (nums.empty()) return 0;
       int soFar = nums.size() + 1, left = 0, bag = 0;

       bag = nums[left];
       if (bag >= s) {            // <--------- XXX
          return 1;
       }

       for (int i = 1; i < nums.size(); ++i) {
          bag += nums[i];
          while (bag >= s) {
             soFar = min(soFar, i - left + 1);
             bag -= nums[left];
             left++;
          }
       }

       return soFar % (nums.size() + 1);
    }
};


/*
 * forget to consider edge case
 * where answer consists only one value window for the first value.
 */

/*
TESTS
7
[2,3,1,2,4,3]
2
[1, 1]
2
[1]
3
[1, 1, 1]
6
[10, 1, 1]
*/
