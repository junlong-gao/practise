class Solution {
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int lo = 0; int hi = 0;
        for (auto w : weights) {
            hi += w;
            lo = max(lo, w);
        }
        lo--;
        auto checker = [&](int cap) {
            int running_total = 0;
            int count = 1;
            for (int i = 0; i < weights.size(); ++i) {                
                if (running_total + weights[i] > cap) {
                    count++;
                    running_total = weights[i];
                } else {
                    running_total += weights[i];
                }
            }  
            
            return count <= D;
        };
        
        while (lo + 1 < hi) {
            int m = lo + (hi - lo) / 2;
            if (checker(m)) {
                hi = m;
            } else {
                lo = m;
            }
        }
        
        return hi;
    }
};
