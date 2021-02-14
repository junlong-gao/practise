class Solution {
    /*
    Key insighes:
    1. consider for each element, calculate its left most element that lower than it.
       ---> use a stack
    2. when adding the element to the set, all candidates in the set has the element
       as the right most element lower than element
    
    */
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        vector<int> s;
        s.push_back(-1);
        int cur_max = 0;
        for(int i = 0; i < heights.size(); ++i){
            while(s.back() != -1 && heights[i] <= heights[s.back()]){
                int top = s.back(); s.pop_back();
                cur_max = max(cur_max, heights[top] * (i - s.back() - 1));
            }
            s.push_back(i);
        }
        return cur_max;
    }
};