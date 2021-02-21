class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        vector<int> pfx{0};
        for (auto e : nums) {
            pfx.push_back(pfx.back() + e % 2);
        }
        int ret = 0;
        for (int i = 0; i < pfx.size(); ++i) {
            auto bit = lower_bound(pfx.begin(), pfx.begin() + i, pfx[i] - k);
            auto eit = upper_bound(pfx.begin(), pfx.begin() + i, pfx[i] - k);
            ret += eit - bit;
        }
        return ret;
    }
};
