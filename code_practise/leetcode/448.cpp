class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < nums.size(); ++i) {
            while(nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        vector<int> ret;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i + 1) ret.push_back(i + 1);
        }
        return ret;
    }
};
