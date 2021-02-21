
class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        int N = A.size();
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int l, int r) {
           return B[l] < B[r];
        });
        vector<int> ret(N, -1), copyA(A.begin(), A.end());
        sort(copyA.begin(), copyA.end());
        int cur = 0, used = 0;
        while (cur < copyA.size() && used < B.size()) {
            while (cur < copyA.size() && copyA[cur] <= B[idx[used]]) {
                cur++;
            }
            if (cur < copyA.size()) {
                ret[idx[used]] = copyA[cur];
                copyA[cur] = -1;
            }
            cur++; used++;
        }

        cur = 0; used = 0;
        while (cur < ret.size() && used < copyA.size()) {
            while(cur < ret.size() && ret[cur] >= 0) {
                cur++;
            }
            while (used < copyA.size() && copyA[used] < 0) {
                used++;
            }
            if (cur < ret.size() && used < copyA.size()) {
               ret[cur] = copyA[used];
               cur++; used++;
            }
        }
        return ret;
    }
};

