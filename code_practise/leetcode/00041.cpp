class Solution {
    /*
    key idea: e <= 0 or e > nums.size() does not contribute to the solution
    */
public:
    int firstMissingPositive(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] <= 0) {
                nums[i] = 0;
            }
            if (nums[i] > nums.size()) {
                nums[i] = nums.size() + 1;
            }
        }
        
        for (int i = 0; i < nums.size(); ++i) {
            int val = nums[i] & ((1U << 31) - 1);
            if (val == 0 || val == nums.size() + 1) {
                continue;
            }
            nums[val - 1] = nums[val - 1] | (1<<31);
        }
        for (int i = 0; i < nums.size(); ++i) {
            int bit = nums[i] >> 31;
            if (bit == 0) {
                return i + 1;
            }
        }
        return nums.size() + 1;
    }
};
