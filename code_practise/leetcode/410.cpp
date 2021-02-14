class Solution {
    /*
    fffffttt
    */
public:
    int splitArray(vector<int>& nums, int m) {
        int lo = 0; int hi = [&]() {
            int ret = 0;
            for (auto p : nums) {
                ret += p;
            }
            return ret;
        }();
        
        auto check = [&nums, &m](int x) {
            int used = 1;
            int running = 0;
            for (int i = 0; i < nums.size(); ++i) {
                if (nums[i] > x) {
                    return false;
                }
                if (running + nums[i] > x) {
                    used++;
                    running = 0;
                }
                running += nums[i];
            }
            
            return used <= m;
        };
        while (hi - lo > 1) {
            int mid = lo + (hi - lo) / 2;
            if (check(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        
        return hi;
    }
};