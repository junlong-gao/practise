/*
 * lcg 480
 *  ✔ Accepted
 *  ✔ 42/42 cases passed (89 ms)
 *  ✔ Your runtime beats 15.72 % of cpp submissions
 *
 * [480] Sliding Window Median
 *
 * https://leetcode.com/problems/sliding-window-median/description/
 *
 * algorithms
 * Hard (30.71%)
 * Total Accepted:    12.5K
 * Total Submissions: 40.6K
 * Testcase Example:  '[1,3,-1,-3,5,3,6,7]\n3'
 *
 * Median is the middle value in an ordered integer list. If the size of the
 * list is even, there is no middle value. So the median is the mean of the two
 * middle value.
 * Examples:
 * [2,3,4] , the median is 3
 * [2,3], the median is (2 + 3) / 2 = 2.5
 *
 * Given an array nums, there is a sliding window of size k which is moving
 * from the very left of the array to the very right. You can only see the k
 * numbers in the window. Each time the sliding window moves right by one
 * position. Your job is to output the median array for each window in the
 * original array.
 *
 * For example,
 * Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.
 *
 *
 * Window position                Median
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       1
 * ⁠1 [3  -1  -3] 5  3  6  7       -1
 * ⁠1  3 [-1  -3  5] 3  6  7       -1
 * ⁠1  3  -1 [-3  5  3] 6  7       3
 * ⁠1  3  -1  -3 [5  3  6] 7       5
 * ⁠1  3  -1  -3  5 [3  6  7]      6
 *
 *
 * Therefore, return the median sliding window as [1,-1,-1,3,5,6].
 *
 * Note:
 * You may assume k is always valid, ie: k is always smaller than input array's
 * size for non-empty array.
 */
class Solution {
   struct kv {
      int index;
		long long value;
      bool operator<(const kv &r) const {
         if (value != r.value) {
            return value < r.value;
         }

         return index < r.index;
      }
   };

   struct medianSet {
      set<kv> up, down; // index -> value;
      int k; // k + 1 for up, k for down
      medianSet(int d) {
         k = d / 2;
      }

      void insert(int index, int v) {
         kv value {index, v};

         if (up.empty()) {
            up.insert(value);
            return;
         }

         if (up.size() == down.size()) {
            if (v >= down.rbegin()->value) {
               up.insert(value);
            } else {
               up.insert(*(down.rbegin()));
               down.erase(*(down.rbegin()));
               down.insert(value);
            }
         } else {
            if (v <= up.begin()->value) {
               down.insert(value);
            } else {
               down.insert(*(up.begin()));
               up.erase(*(up.begin()));
               up.insert(value);
            }
         }
      }

      void remove(int index, int v) {
         kv value {index, v};

         if (up.size() == down.size()) {
            if (down.find(value) != down.end()) {
               down.erase(value);
            } else {
               up.erase(value);
               up.insert(*down.rbegin());
               down.erase(*down.rbegin());
            }
         } else {
            if (up.find(value) != up.end()) {
               up.erase(value);
            } else {
               down.erase(value);
               down.insert(*up.begin());
               up.erase(*up.begin());
            }
         }
      }

      double report() {
         if (up.size() == down.size()) {
            return (down.rbegin()->value + up.begin()->value) / 2.0;
         }

         return up.begin()->value;
      }
   };
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
       if (nums.empty()) {
          return {};
       }
       medianSet s(k);
       vector<double> ret;
       for (int i = 0; i < nums.size(); ++i) {
          s.insert(i, nums[i]);
          if (i >= k) {
             s.remove(i - k, nums[i - k]);
          }

          if (i + 1 >= k) {
             ret.push_back(s.report());
          }
       }

       return ret;
    }
};

/*
 */

/*
TESTS
[1]
1
[1, 1]
1
[1, 1]
2
[1,3,-1,-3,5,3,6,7]
4
[1,3,-1,-3,5,3,6,7]
5
[1,3,-1,-3,5,3,6,7]
6
[1,3,-1,-3,5,3,6,7]
7
[1,3,-1,-3,5,3,6,7]
8
[1,3,-1,-3,5,3,6,7]
1
[1,3,-1,-3,5,3,6,7]
2
[1,3,-1,-3,5,3,6,7]
3
[2147483647,2147483647]
2
*/
