class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int b = 1 << nums.size();
        vector<vector<int>> ret;
        for (int i = 0; i < b; ++i) {
            int idx = i; ret.push_back({});
            for (int k = 0; k < nums.size(); ++k) {
                if (idx & (1 << k)) {
                    ret.back().push_back(nums[k]);
                }
            }
        }
        
        return ret;
    }
};
