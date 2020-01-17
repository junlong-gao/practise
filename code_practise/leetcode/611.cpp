class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.rbegin(), nums.rend());
        int ret = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int l = i + 1; int r = nums.size() - 1;
            while (l < r) {
                if (nums[l] + nums[r] > nums[i]) {
                    ret += r - l;
                    l++;
                } else {
                    r--;
                }
            }
            
        }
        return ret;
    }
};