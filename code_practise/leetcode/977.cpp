class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int pivit = 0;
        int minAbs = INT_MAX;
        for (int i = 0; i < nums.size(); ++i) {
            if (abs(nums[i]) < minAbs) {
                pivit = i;
                minAbs = abs(nums[i]);
            }
        }

        vector<int> ret;
        int l = pivit, r = pivit + 1;
        while (l >= 0 && r < nums.size()) {
            if (nums[l] * nums[l] <= nums[r] * nums[r]) {
                ret.push_back(nums[l] * nums[l]);
                l--;
            } else {
                ret.push_back(nums[r] * nums[r]);
                r++;
            }
        }
        while (l >= 0) {
            ret.push_back(nums[l] * nums[l]);
            l--;
        }
        while (r < nums.size()) {
            ret.push_back(nums[r] * nums[r]);
            r++;
        }

        return ret;
    }
};