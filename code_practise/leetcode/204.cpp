class Solution {
public:
    int countPrimes(int n) {
        int ret = 0;
        vector<bool> bits(n);
        for (int i = 2; i < n; ++i) {
            if (bits[i]) continue;
            ret++;
            for (int k = 1; k * i < n; ++k) {
                bits[k * i] = true;
            }
        }
        
        return ret;
    }
};