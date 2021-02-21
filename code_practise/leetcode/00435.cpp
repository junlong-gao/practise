class Solution {
    /*
    Sort by starting point.
    When consider an interval int, if it does not overlap with
    previous set, add it to the set greedily. Otherwise, it must
    overlap with the last element in the set only. Remove the one
    having a further endpoint greedily.
    */
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        sort(intervals.begin(), intervals.end(), 
            [](const vector<int> &l, const vector<int> &r) {
                return l[0] < r[0];
            });
        int curEnd = intervals[0][1];
        int removed = 0;
        for (int i = 1; i < intervals.size(); ++i) {
            if (curEnd > intervals[i][0]) {
                removed++;
                curEnd = min(curEnd, intervals[i][1]);
            } else {
                curEnd = intervals[i][1];
            }
        }
        
        return removed;
    }
};