class Solution {
/*
start at x, k terms
x >= 1, k >= 1

2x = 2N/k - k + 1

1. 2N % k = 0
2. 2N/k - k + 1 is a positive even integer.
*/
public:
    int consecutiveNumbersSum(int N) {
        int count = 0;
        for (int k = 1; k * k <= 2*N; ++k) {
            if (2 * N % k == 0 && (2 * N / k - k + 1 >= 2) && (2 * N / k - k + 1) % 2 == 0) {
                count++;
            }
        }
        
        return count;
    }
};
