class Solution {
/*
if height[l] < height[r], the limiting factor is on the right, just add up the max left height - current left height and advance l
*/
public:
    int trap(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int ret = 0;
        int lm = 0, rm = 0;
        while (l < r) {
            if (height[l] < height[r]) {
                if (height[l] > lm) {
                    lm = height[l];
                } else {
                    ret += lm - height[l];
                }
                l++;
            } else {
                if (height[r] > rm) {
                    rm = height[r];
                } else {
                    ret += rm - height[r];
                }
                r--;
            }
        }
        
        return ret;
    }
};
