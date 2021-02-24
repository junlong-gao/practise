class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        map<int, int> refcount;
        for (auto e : nums) {
            refcount[e]++;
        }
        int n = nums.size();
        while (n) {
            auto it = refcount.begin();
            int nextVal = it->first;
            for (int i = 0; i < k; ++i, ++nextVal, --n) {
                if (it == refcount.end() || it->first != nextVal || it->second == 0) {
                    return false;
                }
                it->second--;
                if (it->second == 0) {
                    it = refcount.erase(it);
                } else {
                    ++it;
                }
            }
        }
        return true;
    }
};