/*
find the first largest index i >= 0 such that
nums[i] < nums[i + 1]
if no such i is possible, the entire array is in decending order. it has no next permuation.
otherwise, fix this i. From the end, find another index j < i such that nums[j] > nums[i] and is the smallest.
swap(nums[i], nums[j])
reverse nums[i + 1] ... nums[last]

example:
0 1 2 3 4
2 5 4 3 1
i = 0
j = 3
swap:
3 5 4 2 1
reverse:
3 1 2 4 5

0 1 2
2 3 1
i = 0
j = 1
3 2 1
3 1 2
*/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() <= 1) return;
        int i = nums.size() - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) --i;
        if (i < 0) {
            reverse(nums.begin(), nums.end());
            return;
        }
        int j = nums.size() - 1;
        while (j > i && nums[j] <= nums[i]) --j;
        swap(nums[i], nums[j]);
        reverse(nums.begin() + i + 1, nums.end());
    }
};