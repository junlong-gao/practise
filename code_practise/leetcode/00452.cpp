class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;
        sort(points.begin(), points.end(),
            [](const vector<int> &l,
               const vector<int> &r) {
                if (l[0] != r[0]) {
                    return l[0] < r[0];
                }
                return l[1] < r[1];
            });
        int count = 1; 
        int curBegin = points[0][0]; int curEnd = points[0][1];
        for (int i = 1; i < points.size(); ++i) {
           if (points[i][0] > curEnd) {
               count++;
               curEnd = points[i][1];
               curBegin = points[i][0];
           } else {
               curEnd = min(points[i][1], curEnd);
               curBegin = max(points[i][0], curBegin);
           }
        }
        return count;
    }
};
