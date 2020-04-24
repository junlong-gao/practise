class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        int i = 0, j, k, l;
        while (i < nums.size()) {
            j = i + 1;
            while (j < nums.size()) {
                k = j + 1;
                l = nums.size() - 1;

                while (k < l) {
                   if (nums[k] + nums[l] == target - (nums[i] + nums[j])) {
                       ret.emplace_back(vector<int>{nums[i], nums[j], nums[k], nums[l]});
                   }
                   if (nums[k] + nums[l] < target - (nums[i] + nums[j])) {
                       k++;
                       while (k < l && nums[k] == nums[k - 1]) {
                           k++;
                       }
                   } else {
                       l--;
                       while (k < l && nums[l] == nums[l + 1]) {
                           l--;
                       }
                   }
                }

                j++;
                while(j < nums.size() && nums[j] == nums[j - 1]) {
                    j++;
                }
            }
            i++;
            while (i < nums.size() && nums[i] == nums[i - 1]) {
                i++;
            }
        }
        return ret;
    }
};