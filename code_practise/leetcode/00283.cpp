class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i = 0; int j = 0;
        // [0, i) not 0, [i, j) all 0, [j, end) not processed
        while (j < nums.size()) {
            if (nums[j] != 0) {
                swap(nums[i], nums[j]);   
                i++;
            }
            j++;
        }
    }
};