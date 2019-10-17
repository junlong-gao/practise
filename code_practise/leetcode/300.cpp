class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = lower_bound(tails.begin(), tails.end(), nums[i]);
            if (it == tails.end()) {
                tails.push_back(nums[i]);
            } else {
                *it = nums[i];
            }
        }
        
        return tails.size();
    }
};
