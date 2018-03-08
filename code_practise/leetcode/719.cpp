/*
 * > leetcode submit 719.cpp
 *   ✔ Accepted
 *   ✔ 19/19 cases passed (29 ms)
 *   ✔ Your runtime beats 38.43 % of cpp submissions
 *
 * [719] Find K-th Smallest Pair Distance
 *
 * https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/
 *
 * algorithms
 * Hard (26.95%)
 * Total Accepted:    5.7K
 * Total Submissions: 21.3K
 * Testcase Example:  '[1,3,1]\n1'
 *
 * Given an integer array, return the k-th smallest distance among all the
 * pairs. The distance of a pair (A, B) is defined as the absolute difference
 * between A and B. 
 * 
 * Example 1:
 * 
 * Input:
 * nums = [1,3,1]
 * k = 1
 * Output: 0 
 * Explanation:
 * Here are all the pairs:
 * (1,3) -> 2
 * (1,1) -> 0
 * (3,1) -> 2
 * Then the 1st smallest distance pair is (1,1), and its distance is 0.
 * 
 * 
 * 
 * Note:
 * 
 * 2 .
 * 0 .
 * 1 .
 * 
 *
 * Digestion:
 * This is a fest of binary search. Review it from time to time.
 * Rule of thumb: the kth element in a sorted array is the first value
 * such that ele <= toFind is true:
 * 2 2 3 5 5 6
 * k = 4, toFind = 5
 * f f f t t t
 * 6 also satisfies, but 5 is smaller, and 4 does not satisfy (not in the array).
 */
class Solution {
   vector<int> vals;
   int count(int d, int offset) {
      int lo = 0, hi = vals.size() - offset - 1;
      //cout << "called: " << d << " " << offset << endl;
      if (hi == 0) return 0;

      //[lo, hi)
      // count the number of distance from vals[offset] to vals[k] (k >= offset, k < vals.size, vals.size() - offset different distances)
      // <= d
      while (hi - lo > 1) {
         int mid = lo + (hi - lo) / 2;
         int ds = vals[offset + mid + 1] - vals[offset];
         if (d >= ds) {
            lo = mid;
         } else {
            hi = mid;
         }
      }

      //cout << "@@@" << lo << endl;

      return (d >= (vals[offset + lo + 1] - vals[offset])) ? lo + 1 : 0;
   }


public:
   int smallestDistancePair(vector<int>& nums, int k) {
      std::swap(nums, vals);

      std::sort(vals.begin(), vals.end());
      int lo = -1, hi = vals.back();

      while (hi - lo > 1) {
         int mid = lo + (hi - lo) / 2;
         int c = 0;
         for (int i = 0; i < vals.size(); ++i) {
            c += count(mid, i);
         }

         //cout << c << " " << lo << " " << hi << endl;
         if (c >= k) {
            hi = mid;
         } else {
            lo = mid;
         }
      }

      return hi;
   }
};


/*
 *
*/

/*
TESTS
[1,1, 2, 3, 3, 4, 5, 5, 6]
7
[1,3,1]
1
[1,3,1]
2
[1,3,1]
3
[1,1, 2, 3, 3, 4, 5, 5, 6]
1
[1,1, 2, 3, 3, 4, 5, 5, 6]
2
[1,1, 2, 3, 3, 4, 5, 5, 6]
3
[1,1, 2, 3, 3, 4, 5, 5, 6]
4
[1,1, 2, 3, 3, 4, 5, 5, 6]
5
[1,1, 2, 3, 3, 4, 5, 5, 6]
6
[1,1, 1, 1, 1, 1, 1, 1, 1]
1
[1,1, 1, 1, 1, 1, 1, 1, 1]
9
*/
