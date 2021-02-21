class Solution {
public:
    int maximumSwap(int num) {
        vector<int> d;
        long long m = num;
        while (num) {
            d.push_back(num % 10);
            num /= 10;
        }
        
        for (int i = 0; i < d.size(); ++i) {
            for (int j = i + 1; j < d.size(); ++j) {
                swap(d[i], d[j]);
                long long t = 0;
                for (int k = d.size() - 1; k >= 0; --k) {
                    t *= 10;
                    t += d[k];
                }
                
                m = max(m, t);
                swap(d[i], d[j]);
            }
        }
        
        return m;
    }
};
