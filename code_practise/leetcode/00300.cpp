class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> ends;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = lower_bound(ends.begin(), ends.end(), nums[i]);
            if (it == ends.end()) {
                // lower_bound ensures this nums[i] larger than any:
                ends.push_back(nums[i]);
            } else {
                *it = nums[i];
            }
        }
        
        return ends.size();
    }
};