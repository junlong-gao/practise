class Solution {
    struct pt {
        int idx;
        int val;
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<pt> q;
        vector<int> ret;
        for (int i = 0; i <nums.size(); ++i) {
            while (q.size() > 0 && q.back().val <= nums[i]) {
                q.pop_back();
            }
            q.push_back(pt{i, nums[i]});
            while (q.size() > 0 && q.front().idx + k <= i) {
                q.pop_front();
            }
            
            if (i + 1 >= k) {
                ret.push_back(q.front().val);
            }
        }
        return ret;
    }
};
