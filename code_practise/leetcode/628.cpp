class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ret = nums[nums.size() - 1] * nums[nums.size() - 2] * nums[nums.size() - 3];
        ret = max(ret, nums[nums.size() - 1] * nums[nums.size() - 2] * nums[0]);
        ret = max(ret, nums[nums.size() - 1] * nums[1] * nums[0]);
        ret = max(ret, nums[2] * nums[1] * nums[0]);
        return ret;
    }
};