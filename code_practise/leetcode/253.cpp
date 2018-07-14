/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> p;
        for (const auto & i : intervals) {
            p[i.start] += 1;
            p[i.end] -= 1;
        }

        int cur = 0; int best = 0;
        for (auto it = p.begin(); it != p.end(); ++it) {
            cur += it->second;
            best = max(best, cur);
        }
        return best;
    }
};

/*
cf. Skyline
cf. count rect area
*/
