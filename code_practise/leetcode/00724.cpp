class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i) {
            sum+=nums[i];
        }
        int running = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (running == sum - running - nums[i]) {
                return i;
            }
            running += nums[i];
        }
        
        return -1;
    }
};
