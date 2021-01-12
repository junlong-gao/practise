class Solution {
    struct ent_t {
        int s; int f;
    };
public:
    vector<int> partitionLabels(string S) {
       vector<ent_t> lk(256, ent_t{-1, -1});
       for (int i = 0; i < S.size(); ++i) {
           if (lk[S[i]].s == -1) {
               lk[S[i]].s = i;
           }
           lk[S[i]].f = i;
       }
       int i = 1;
       int curStart = lk[S[0]].s;
        vector<int> ret{lk[S[0]].f - lk[S[0]].s + 1};
        while (i < S.size()) {
            if (lk[S[i]].s < curStart + ret.back() - 1) {
                ret.back() = max(ret.back(), lk[S[i]].f - curStart + 1);
            } else {
                assert(curStart + ret.back() - 1 + 1 == i);
                assert(lk[S[i]].s == i);
                ret.push_back(lk[S[i]].f - lk[S[i]].s + 1);
                curStart = lk[S[i]].s;
            }
            i++;
        }
        return ret;
    }
};
