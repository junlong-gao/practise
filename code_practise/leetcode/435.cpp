class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        sort(intervals.begin(), intervals.end(), 
            [](const vector<int> &l,
               const vector<int> &r) {
                if (l[0] !=r[0]) {
                    return l[0] < r[0];
                }
                return l[1] < r[1];
            });
        int count = 0; int curEnd = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i) {
            if (curEnd > intervals[i][0]) {
                count++;
                curEnd = min(curEnd, intervals[i][1]);
            } else {
                curEnd = intervals[i][1];
            }
        }
        return count;
    }
};
