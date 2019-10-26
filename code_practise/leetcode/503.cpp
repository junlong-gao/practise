class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> s;
        vector<int> ret(nums.size(), -1);
        for (int i = 0; i < 2 * nums.size(); i++) {
            while (s.size() && nums[i % (nums.size())] > nums[s.back()]) {
                ret[s.back()] = nums[i % (nums.size())];
                s.pop_back();
            }
            if (i < nums.size()) {
                s.push_back(i);
            }
        }
        
        return ret;
    }
};
