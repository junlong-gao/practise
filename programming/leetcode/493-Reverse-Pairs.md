## Tag:
* divided and conquer
* two pointers

## AC version:
```C++
class Solution {
    int total;
public:
    int reversePairs(vector<int>& nums) {
        mergeSort(0, nums.size(), nums);
        return total;
    }
    
    void mergeSort(int i, int j, vector<int>& nums) {
        if (j <= i + 1) return;
        int l = i + (j - i)/2;
        mergeSort(i, l, nums);
        mergeSort(l, j, nums);
        
        int k = i, m = l;
        while (k < l && m < j) {
            while (m < j && (long long)nums[k] > 2 * (long long)nums[m]) m++;
            total += (m - l);
            k++;
        }
        total += (l - k) * (m - l);
        // or use real mergesort.
        sort(nums.begin() + i, nums.begin() + j);
        return;
    }
};
```

## Notes
Note that there is an easy generalization:

Let f(x, y) to be a binary predicate over sequence S. 

If there exists a partition strategy p = part(i,j) such that, 
 \forall k \in range [i, p), \forall l \in [p, j) such that 
  f(S[k], S[l]) is true => \forall m \in [l, j), f(S[k], S[m) is true, 
then this solution can be easily generalized.

For example, it is trivial to verify that i < j && nums[i] > 2 * nums[j] is a such f with part(i, j) = i + (j-i)/2
