class Solution {
    struct p {
        int f, s;
    };
public:
    vector<int> partitionLabels(string S) {
        vector<int> count;
        vector<p> intervals(256, p{-1, -1});
        for (size_t i = 0; i < S.size(); ++i) {
            if (intervals[S[i]].f == -1) {
                intervals[S[i]].f = i;
            }
            
            intervals[S[i]].s = i;
        }
        
        int i = 0;
        p cur = intervals[S[i++]];
        while (i < S.size()) {
            p next = intervals[S[i]];
            if (next.f <= cur.s) {
                cur.s = max(cur.s, next.s);
            } else {
                assert(cur.s == next.f - 1);
                count.push_back(cur.s - cur.f + 1);
                cur = next;
            }
            i++;
        }
        count.push_back(cur.s - cur.f + 1);
        return count;
    }
};
