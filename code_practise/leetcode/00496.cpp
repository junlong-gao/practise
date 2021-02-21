class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        vector<int> s;
        vector<int> ret;
        unordered_map<int, int> ans;
        for (int i = nums.size() - 1; i >= 0; --i) {
            while(!s.empty() && s.back() <= nums[i]) {
                s.pop_back();
            }
            if (s.empty()) {
                ans[nums[i]] = -1;
            } else {
                ans[nums[i]] = s.back();
            }
            s.push_back(nums[i]);
        }
        for (auto v : findNums) {
            ret.push_back(ans[v]);
        }
        return ret;
    }
};
