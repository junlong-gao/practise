/*
Consider input array:

value: -infty 1 2 3 1 -infty

and its first order derivative:

derivative: -infry, 1, 1, -2, +infty

derivative at index i is array[i] - array[i - 1]

To find a peak element index, is to find a positive direvative so that the previous direvative is nagative.

Now, if we have a range of direvatives with least 2 values, 
first being negative and the last being positive.
Then there must exist a direvative in the array such 
that itself is positive and the previous value of it is nagative.

Let lo = 0, hi = array.size()
Inititially, we have
derivative at lo: -infty < 0
derivative at hi: +infty > 0
So there must be a peak value in index range [lo, hi)

To maintain the invariant, pick any element mid in (lo, hi):
If derivative at mid is negative:
<0,     +infty > 0
[mid,    hi)
Then the peak value is in index range [mid, hi)

if derivative at mid is positive:
-infty < 0,    > 0
       [lo,    mid)
then the peak value is in index range [lo, mid)

This can be regarded as the discrete version of the intermediate theorem.

*/
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int lo = 0, hi = nums.size();
        while (hi - lo > 1) {
            int mid = lo + (hi - lo) / 2;
            int sign = nums[mid] - nums[mid - 1];
            if (sign < 0) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        return lo;
    }
};
