class Solution {
    /*
    If we fix the smallest edge, and smallest + nums[l] <= nums[r],
    it is not conclusive whether we should do l++ or r--.
    
    If we fix the largest edge, and nums[l] + nums[r] <= largest edge,
    we can immediately know to do l++;
    
    Also, since we do r-- if it can form a triangle, to avoid double counting,
    we are counting all possible choices of l for each r.
    */
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ret = 0;
        for (int i = nums.size() - 1; i >= 0; --i) {
            int r = i - 1; int l = 0;
            while (l < r) {
                if (nums[l] + nums[r] > nums[i]) {
                    ret += r - l; // all possible choices of l
                    r--;
                } else {
                    l++;
                }
            }
        }
        
        return ret;
    }
};