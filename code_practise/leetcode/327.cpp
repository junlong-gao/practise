/*
 * > lcsubmit 327
 *   ✔ Accepted
 *   ✔ 61/61 cases passed (32 ms)
 *   ✔ Your runtime beats 39.63 % of cpp submissions
 *
 * [327] Count of Range Sum
 *
 * https://leetcode.com/problems/count-of-range-sum/description/
 *
 * algorithms
 * Hard (30.56%)
 * Total Accepted:    22.8K
 * Total Submissions: 74.5K
 * Testcase Example:  '[-2,5,-1]\n-2\n2'
 *
 *
 * ⁠   Given an integer array nums, return the number of range sums that lie in
 * [lower, upper] inclusive.
 *
 * ⁠   Range sum S(i, j) is defined as the sum of the elements in nums between
 * indices i and
 * ⁠   j (i ≤ j), inclusive.
 *
 *
 *
 * ⁠   Note:
 * ⁠   A naive algorithm of O(n2) is trivial. You MUST do better than that.
 *
 *
 * ⁠   Example:
 * ⁠   Given nums = [-2, 5, -1], lower = -2, upper = 2,
 * ⁠   Return 3.
 * ⁠   The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums
 * are: -2, -1, 2.
 *
 *
 * Credits:Special thanks to @dietpepsi for adding this problem and creating
 * all test cases.
 */

/*
 * Observation
 * 1. If we use S[i] = sum [0, i), S[j] - S[i] = S(i, j - 1) is still
 *    enough to represent all possible partial sums. This version is
 *    easier to work with.
 * 2. Similar to 315, if we know count of [s, mid) and [mid, e), we can 
 *    construct the count for [s, e) by finding all pairs of i j such that
 *    lower <= S[j] - S[i] <= upper.
 *    This can be done by tracking two index l and k
 *    l: the largest index in [mid, e) such that
 *    S[l] - S[i] <= upper
 *    k: the largest index in [mid, e) such hat
 *    S[k] - S[i] < lower
 *    Then for this i, we add count l - k, and advance i, and update k and l.
 *    After these, we do a normal merge sort. So really it is the sorted
 *    [s, mid) helped us.
 *
 * There are many interesting consideration to this approach (generalization?)
 * Note 315.
 */
class Solution {
   using ll = long long;
   vector<ll> sum;
   int count = 0;
   ll upper, lower;
   vector<ll> merge(int s, int e) {
      if (e - s == 0) return {};
      if (e - s == 1) return {sum[s]};

      int mid = s + (e - s)/2;
      vector<ll> left, right, ret;
      left  = merge(s, mid);
      right = merge(mid, e);
      int j = 0, k = 0, l = 0;
      for (int i = 0; i < left.size(); ++i) {
         while (l < right.size() && right[l] - left[i] <= upper) l++;
         while (k < right.size() && right[k] - left[i] < lower) k++;
         count += (l - k);
      }

      int i = 0;
      while (i < left.size() && j < right.size()) {
         if (left[i] < right[j]) {
            ret.push_back(left[i++]);
         } else {
            ret.push_back(right[j++]);
         }
      }

      while (i < left.size()) {
         ret.push_back(left[i++]);
      }

      while (j < right.size()) {
         ret.push_back(right[j++]);
      }

      return ret;
   }

public:
    int countRangeSum(vector<int>& nums, int lo, int up) {
       sum.push_back(0);
       for (int i = 0; i < nums.size(); ++i) {
          sum.push_back(sum.back() + nums[i]);
       }

       upper = up; lower = lo;
       merge(0, sum.size());
       return count;
    }
};


/*
TESTS
[-2, 5, -1]
-2
2
[-2, 5]
-2
2
[-2]
-2
2
[-2147483647,0,-2147483647,2147483647]
-564
3864
*/
