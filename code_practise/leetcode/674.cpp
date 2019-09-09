class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        int ret = 1;
        for (int i = 1, j = 0; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1]) {
                ret = max(ret, i - j + 1);
            } else {
                j = i;
            }
        }
        
        return ret;
    }
};
