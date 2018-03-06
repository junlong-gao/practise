/*
 * [689] Maximum Sum of 3 Non-Overlapping Subarrays
 *
 * https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/description/
 *
 * algorithms
 * Hard (40.96%)
 * Total Accepted:    9K
 * Total Submissions: 21.9K
 * Testcase Example:  '[1,2,1,2,6,7,5,1]\n2'
 *
 *
 * In a given array nums of positive integers, find three non-overlapping
 * subarrays with maximum sum.
 *
 *
 * Each subarray will be of size k, and we want to maximize the sum of all 3*k
 * entries.
 *
 *
 * Return the result as a list of indices representing the starting position of
 * each interval (0-indexed).  If there are multiple answers, return the
 * lexicographically smallest one.
 *
 * Example:
 *
 * Input: [1,2,1,2,6,7,5,1], 2
 * Output: [0, 3, 5]
 * Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting
 * indices [0, 3, 5].
 * We could have also taken [2, 1], but an answer of [1, 3, 5] would be
 * lexicographically larger.
 *
 *
 *
 * Note:
 * nums.length will be between 1 and 20000.
 * nums[i] will be between 1 and 65535.
 * k will be between 1 and floor(nums.length / 3).
 *
 * Digestion:
 * Key observation:
 * The index of the middle interval can be in [k, n - 2k)
 * for all i \in [k, n - 2k), we need to rapidly answer
 * 1) what is the window size k in range [0, i - k] has the largest sum?
 * 2) what is the window size k in range [i + k, n - k] has the largest sum?
 * These can be answered quickly and trivially by precomputing a table:
 * left[i] = the start index of the largest window of size k in range [0, i]
 *         = max(left[i - 1], sum(i - k + 1, i + 1))
 * left[0] = 0 (sum(k) - sum(0));
 */
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
       int n = nums.size();
       vector<int> sum(n + 1, 0), left(n, 0), right(n, 0);
       for (int i = 0; i < n; ++i) {
          sum[i + 1] = sum[i] + nums[i];
       }

       left[0] = 0;
       int soFar = sum[k] - sum[0];
       for (int i = 1; i + k < n; ++i) {
          if (sum[i + k] - sum[i] > soFar) {
             left[i] = i;
             soFar = sum[i + k] - sum[i];
          } else {
             left[i] = left[i - 1];
          }
       }

       right[n - k] = n - k;
       soFar = sum[n] - sum[n - k];
       for (int i = n - k - 1; i >= 0; --i) {
          if (sum[i + k] - sum[i] >= soFar) {
             right[i] = i;
             soFar = sum[i + k] - sum[i];
          } else {
             right[i] = right[i + 1];
          }
       }

       soFar = INT_MIN;
       vector<int> ret;
       for (int i = k; i <= n - 2 * k; ++i) {
          int l = left[i - k], r = right[i + k];
          int val = sum[i + k] - sum[i] + sum[l + k] - sum[l] + sum[r + k] - sum[r];
          if (val > soFar) {
             soFar = val;
             ret = {l, i, r};
          }
       }

       return ret;
    }
};


/*
TESTS
[1, 1, 1]
1
[1,2,1,2,6,7,5,1]
2
[1,2,1,2,6,7,1,2,5,1]
3
*/
