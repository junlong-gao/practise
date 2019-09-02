class Solution {
    int helper(vector<int> &nums, int i, int j, int k) {
        // find kth largest element in range [i, j), j > i
        if (j == i + 1) {
            return nums[i];
        }
        int mid = i + (j - i) / 2; 
        swap(nums[i], nums[mid]); int p = i;
        for (int l = i + 1; l < j; ++l) {
            if (nums[l] >= nums[i]) {
                p++; swap(nums[p], nums[l]);
            }
        }
        swap(nums[p], nums[i]);
        if (p - i == k) {
            return nums[p];
        } else if (p - i > k) {
            return helper(nums, i, p, k);
        } else {
            return helper(nums, p, j, (k - (p - i)));
        }
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        return helper(nums, 0, nums.size(), k - 1);
    }
};
