class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> pfx{0};
        for (int i = 0; i < nums.size(); ++i) {
           pfx.push_back(pfx.back() + nums[i]);
        }

        int runMin = pfx[0];
        int ret = pfx[1];
        for (int i = 1; i < pfx.size(); ++i) {
           ret = max(ret, pfx[i] - runMin);
           runMin = min(runMin, pfx[i]);
        }

        return ret;
    }
};
