class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int H) {
        int lo = 0; int hi = 0;
        for (int i = 0; i < piles.size(); ++i) {
            hi = max(hi, piles[i]);
        }
        while (hi - lo > 1) {
            int k = lo + (hi - lo) / 2;
            int t = 0;
            for (int i = 0; i < piles.size(); ++i) {
                t += piles[i] / k;
                if (piles[i] % k) {
                    t++;
                }
            }
            if (t <= H) {
                hi = k;
            } else {
                lo = k;
            }
        }
        return hi;
    }
};