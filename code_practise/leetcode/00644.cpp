static int x=[](){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    double findMaxAverage(const vector<int>& nums, int k) {
      double lo = INT_MAX; double hi = INT_MIN; double e = 1e-7;
      for (auto e : nums) {
        lo = min(lo, (double) e);
        hi = max(hi, (double) e);
      }
      /*
      f f f f t t t
      */
        auto checker = [&](double x) {
          double cur = 0; double left = 0; double minLeft = 0; // 0 means no element in left
          for (int j = 0; j < (int)nums.size(); ++j) {
            cur += nums[j] - x;
            if (j == k - 1) {
              if (cur >= 0) {
                return false;
              }
            }
            
            if (j + 1 >= k + 1) {
              left += nums[j - k] - x;
              minLeft = min(minLeft, left);
              if (cur - minLeft >= 0) {
                return false;
              }
            }
          }
          return true;
        };
      
        while (abs(hi - lo) >= e) {
          double mid = lo + (hi - lo) / 2;
          if (checker(mid)) {
            hi = mid;
          } else {
            lo = mid;
          }
        }
        
        return lo;
    }
};

/*
idea: maxAve will satisfy:
         \forall i, j \in [0, n) and j - i >= k, \sum_{i<=l<j} num[l] - maxAve < 0.
This is the key observation.

Further, if for x:
          \exist i, j \in [0, n) and j - i >= k,  \sum_{i<=l<j} num[l] - x > 0
We know that x < maxAve

If for some x:
           \forall i, j \in [0, n) and j - i >= k, \sum_{i<=l<j} num[l] - x <= 0.
We know that x >= maxAve

we know maxAve \in [min{num}, max{num}], so we can do binary search

Also note the use of minleft, which keeps track of the min of left part of the sum difference, 
so the maxmium of range sum (which is a difference between left and right pointer with at least
k elements) is tracked. Knowing the maximum can help us answer the case x < maxAve fast, and
if for max range sum <= 0, x >= maxAve is concluded.
*/
