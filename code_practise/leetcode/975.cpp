class Solution {
    vector<int> LU, LL;
    int length;
    bool GO(int idx); unordered_map<int, bool> dpGO;
    bool GE(int idx); unordered_map<int, bool> dpGE;
public:
    int oddEvenJumps(vector<int>& A) {
        LU.resize(A.size(), -1);
        LL.resize(A.size(), -1);
        length = A.size();
        {
            map<int, vector<int>> ge, le;
            for (int i = A.size() - 1; i >= 0; i--) {
                auto leit = le.lower_bound(A[i]);
                auto geit = ge.lower_bound(-A[i]);
                if (leit != le.end()) {
                    LU[i] = leit->second.back();
                }
                if (geit != ge.end()) {
                    LL[i] = geit->second.back();
                }
                le[A[i]].push_back(i);
                ge[-A[i]].push_back(i);
            }
        }

        int count = 0;
        for (int i = 0; i < length; ++i) {
            if (GO(i)) count++;
        }
        return count;
    }
};

bool Solution::GO(int idx) {
    if (idx == -1) return false;
    if (idx == length - 1) return true;
    if (dpGO.count(idx)) return dpGO[idx];
    return dpGO[idx] = (LU[idx] == length - 1 || GE(LU[idx]));
}

bool Solution::GE(int idx) {
    if (idx == -1) return false;
    if (idx == length - 1) return true;
    if (dpGE.count(idx)) return dpGE[idx];
    return dpGE[idx] = (LL[idx] == length - 1 || GO(LL[idx]));
}
