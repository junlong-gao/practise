class Solution {
    /*
    Greedy: at day i, for all the meetings you can attend, attend the event ends the earilest.
    */
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end(), [](const vector<int> &l, const vector<int> &r) {
            if (l[0] != r[0]) {
                return l[0] < r[0];
            }
            return l[1] < r[1];
        });
        int lastDay = 1;
        for (auto e : events) {
            lastDay = max(lastDay, e[1]);
        }
        priority_queue<int, vector<int>, greater<int>> q;
        int ret = 0;
        int idx = 0;
        for (int i = 1; i <= lastDay; ++i) {
            while (q.size() && q.top() < i) {
                q.pop();
            }
            while (idx < events.size() && events[idx][0] == i) {
                q.push(events[idx++][1]);
            }
            if (q.size() && q.top() >= i) {
                q.pop();
                ret++;
            }
        }
        return ret;
    }
};
