class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int ret = 0;
        for(int i = 0; i < 32; ++i){
            int ones = 0;
            for(int j = 0; j < nums.size(); ++j){
                ones += ((nums[j] >> i) & 1);
            }
            ret += ones * (nums.size() - ones);
        }
        return ret;
    }
};