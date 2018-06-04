class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> s;
        vector<int> ret;
        for (int i = nums.size() - 1; i >= 0; --i) {
            s.push_back(nums[i]);
        }
        for (int i = nums.size() - 1; i >= 0; --i) {
            while(!s.empty() && s.back() <= nums[i]) {
                s.pop_back();
            }
            if (s.empty()) {
                ret.push_back(-1);
            } else {
                ret.push_back(s.back());
            }
            s.push_back(nums[i]);
        }
        

        reverse(ret.begin(), ret.end());
        return ret;
    }
};
