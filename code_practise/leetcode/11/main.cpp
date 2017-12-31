//greedy approach
class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0, j = height.size() - 1;
        int area = 0;
        while(i < j){
            int h = min(height[i], height[j]);
            area = max(area, h * (j - i));
            while(height[i] <= h && i < j) ++i;
            while(height[j] <= h && i < j) --j;
        }
        return area;
    }
};