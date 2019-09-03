class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> mp;
        for (auto n : nums1) {
            mp.insert(n);
        }
        vector<int> ret;
        for (auto n : nums2) {
            if (mp.count(n)) {
                ret.push_back(n);
                mp.erase(n);
            }
        }
        
        return ret;
    }
};
