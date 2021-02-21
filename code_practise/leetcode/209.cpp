class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        vector<int> pfx{0};
        for (auto e : nums) {
            pfx.push_back(pfx.back() + e);
        }
        
        int l = -1;
        int best = INT_MAX;
        for (int i = 0; i < pfx.size(); ++i) {
            while (l + 1 < i && pfx[i] - pfx[l+1] >= target) {
                l++;
                best = min(best, i - l);
            }
        }
        
        if (best == INT_MAX) {
            return 0;
        }
        return best;
    }
};