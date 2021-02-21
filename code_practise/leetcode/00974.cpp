class Solution {
    using ll = long long;
public:
    int subarraysDivByK(vector<int>& A, int K) {
        unordered_map<int, ll> refcount;
        refcount[0] = 1;
        int sum = 0;
        for (int i = 0; i < A.size(); ++i) {
            sum += A[i];
            while (sum < 0) {
                sum += K;
            }
            refcount[sum % K]++;
        }
        
        ll ret = 0;
        for (auto &pr : refcount) {
            ret += pr.second * (pr.second - 1) / 2;
        }
        
        return ret;
    }
};
