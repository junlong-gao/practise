class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            swap(nums1, nums2);
        }
        unordered_set<int> nums1C(nums1.begin(), nums1.end());
        vector<int> ret;
        for (auto e : nums2) {
            if (nums1C.count(e)) {
                ret.push_back(e);
                nums1C.erase(e);
            }
        }
        
        return ret;
    }
};