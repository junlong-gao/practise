class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<pair<int, int>> s;
        vector<int> ret(nums.size(), -1);
        for (int i = 0; i < 2 * nums.size(); i++) {
            while (s.size() && nums[i % (nums.size())] > s.back().second) {
                ret[s.back().first] = nums[i % (nums.size())];
                s.pop_back();
            }
            if (i < nums.size()) {
                s.push_back(make_pair(i, nums[i]));
            }
        }
        
        return ret;
    }
};
