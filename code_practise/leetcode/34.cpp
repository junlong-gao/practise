class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) return {-1, -1};
        vector<int> ret;
        {
            int lo = -1, hi = nums.size() - 1;
            while (hi - lo > 1) {
                int m = lo + (hi - lo) / 2;
                if (target <= nums[m]) {
                    hi = m;
                } else {
                    lo = m;
                }
            }
            
            ret.push_back(target == nums[hi] ? hi : -1);
        }
        
        {
            int lo = 0, hi = nums.size();
            while (hi - lo > 1) {
                int m = lo + (hi - lo) / 2;
                if (nums[m] <= target) {
                    lo = m;
                } else {
                    hi = m;
                }
            }
            
            ret.push_back(target == nums[lo] ? lo : -1);
        }
        return ret;
    }
};
