class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        vector<int> ref(K, 0);
        vector<int> pfx{0};
        int ret = 0;
        for (int i = 0; i < A.size(); ++i) {
            pfx.push_back(pfx.back() + A[i]);
        }
        
        for (int i = 0; i < pfx.size(); ++i) {
            int v = pfx[i];
            if (v < 0) {
                v += K * ((0-v) / K + 1);
            }
            
            ret += ref[v%K];
            ref[v%K]++;
        }
        
        return ret;
    }
};