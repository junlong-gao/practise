class Solution {
    int helper(vector<int>& nums, int s, int e) {
        if (s == e || s == e - 1) {
            return 0;
        }
        int mid = s + (e - s) / 2;
        int left = helper(nums, s, mid);
        int right = helper(nums, mid, e);
        int cross = 0;
        
        int i = s, j = mid;
        while (i < mid && j < e) {
            if ((long long) nums[i] <= 2 * (long long) nums[j]) {
                cross += j - mid;
                i++;
            } else {
                j++;
            }
        }
        
        while (i < mid) {
            cross += j - mid;
            i++;
        }
        
        vector<int> out;
        i = s, j = mid;
        while (i < mid && j < e) {
            if (nums[i] <= nums[j]) {
                out.push_back(nums[i]);
                i++;
            } else {
                out.push_back(nums[j]);
                j++;
            }
        }
        
        while (i < mid) {
            out.push_back(nums[i]);
            i++;
        }
        
        while (j < e) {
            out.push_back(nums[j]);
            j++;
        }
        
        for (int i = s; i < e; ++i) {
            nums[i] = out[i-s];
        }
        return left + right + cross;
    }
public:
    int reversePairs(vector<int>& nums) {
        return helper(nums, 0, nums.size());
    }
};

/*
[1,3,2,3,1]
[0]
[1,3]
[3,1]
[]
[2147483647,2147483647,2147483647,2147483647,2147483647,2147483647]
*/
