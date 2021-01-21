class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        int i = 0;
        while (i < nums.size()) {
            int j = i + 1; int l = nums.size() - 1;
            while (j < l) {
                int v = nums[i] + nums[j] + nums[l];
                if (v == 0) {
                    ret.push_back({nums[i], nums[j], nums[l]});
                    j++; l--;
                    while (j < l && nums[j] == nums[j - 1]) {j++;}
                    while (j < l && nums[l] == nums[l + 1]) {l--;}
                } else if (v < 0) {
                    j++;
                } else {
                    l--;
                }
            }
            i++;
            while (i < nums.size() && nums[i] == nums[i - 1]) { i++; }
        }
        
        return ret;
    }
};