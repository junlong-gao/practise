class Solution {
public:
    int binaryGap(int N) {
        int last = -1, cur = 0;
        int best = 0;
        while (N) {
            if (N % 2 == 1) {
                if (last != -1) {
                    best = max(best, cur - last);
                }
                last = cur;
            }
            cur++;
            N /= 2;
        }
        return best;
    }
};