class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        if (nums.size() < 3) return false;
        vector<int> s, m{nums[0]};
        for (int i = 1; i < nums.size(); ++i) {
            m.push_back(min(m.back(), nums[i]));
        }
        for (int i = nums.size() - 1; i >= 0; --i) {
            while (!s.empty() && s.back() <= m[i]) {
                s.pop_back();
            }
            if (nums[i] > m[i]) {
                if (!s.empty() && s.back() < nums[i]) return true;
                s.push_back(nums[i]);
            }
        }
        return false;
    }
};
