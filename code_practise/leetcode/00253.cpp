class Solution {
    struct ent_t {
        int t;
        bool isEnd;
        int idx;
    };
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        vector<ent_t> t;
        for (int i = 0; i < intervals.size(); ++i) {
            t.push_back(ent_t{intervals[i][0], false, i});
            t.push_back(ent_t{intervals[i][1], true, i});
        }
        sort(t.begin(), t.end(), [](const ent_t &l, const ent_t &r) {
            if (l.t != r.t) {
                return l.t < r.t;
            }
            if (l.isEnd != r.isEnd) {
                return l.isEnd;
            }
            return l.idx < r.idx;
        });
        int ret = 0;
        int cur = 0;
        for (int i = 0; i < t.size(); ++i) {
            if (t[i].isEnd) {
                cur--;
            } else {
                cur++;
            }
            ret = max(ret, cur);
        }
        return ret;
    }
};
