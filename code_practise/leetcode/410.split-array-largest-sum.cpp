/*
 * > leetcode submit 410.split-array-largest-sum.cpp
 *   ✔ Accepted
 *   ✔ 27/27 cases passed (5 ms)
 *   ✔ Your runtime beats 40.87 % of cpp submissions
 */
class Solution {
   using ll = long long;
   bool checker(vector<ll> &nums, ll val, ll m) {
      ll bag = nums[0]; m--;
      for (ll i = 1; i < nums.size(); ++i) {
         if (bag + nums[i] > val) {
            m--;
            bag = 0;
         }
         bag += nums[i];
      }
      return m >= 0;
   }

public:
    int splitArray(vector<int>& shortnums, int m) {
       vector<ll> nums(shortnums.begin(), shortnums.end());
       if (nums.empty()) return 0;
       ll minVal = nums[0];
       ll maxVal = minVal;
       for (ll i = 1; i < nums.size(); ++i) {
          maxVal += nums[i];
          minVal = std::max(minVal, nums[i]);
       }

       while(minVal < maxVal) {
          //cout << minVal << " " << maxVal << endl;
          ll mid = minVal + (maxVal - minVal) / 2;
          if (checker(nums, mid, m)) {
             maxVal = mid;
          } else {
             minVal = mid + 1;
          }
       }
       return minVal;
    }
};
