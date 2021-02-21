class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        if (nums.size() < 3) return false;
        // at index i >= 1, P is the smallest element we know have
        // an element before it less than it, Q is the smallest element
        // seen so far.
        int P = INT_MAX, Q = nums.front();
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > P) return true;
            if (nums[i] > Q && nums[i] <= P) P = nums[i];
            if (nums[i] <= Q) Q = nums[i];
        }
        
        return false;
    }
};
