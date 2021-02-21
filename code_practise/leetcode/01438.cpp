class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
       if (nums.empty()) return 0;
        map<int, int> refcount;
        int i = 0; int j = 0;
        int ret = 1;
        while (j < nums.size()) {
           while ((j < nums.size() && (refcount.empty() || (refcount.rbegin()->first - refcount.begin()->first) <= limit))) {
              ret = max(ret, j - i);

              refcount[nums[j]]++;
              j++;
           }

           while (i < j && (!refcount.empty() && (refcount.rbegin()->first - refcount.begin()->first) > limit)) {

              refcount[nums[i]]--;
              if (refcount[nums[i]] == 0) {
                 refcount.erase(nums[i]);
              }
              i++;
           }

           ret = max(ret, j - i);
        }
        return ret;
    }
};
