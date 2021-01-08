class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int ret = 0;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ++i) {
            int j = i + 1; int k = nums.size() - 1;
            while (j < k) {
                if (nums[i] + nums[j] + nums[k] < target) {
                    ret += k - j;
                    j++;
                } else {
                    k--;
                }
            }
        }
        return ret;
    }
};
