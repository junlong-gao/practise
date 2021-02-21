class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> ret;
        for (int i = 0; i < nums.size(); ++i) {
            if (ret.count(target - nums[i])) {
                return {ret[target - nums[i]], i};
            }
            ret[nums[i]] = i;
        }
        assert(0);
    }
};
