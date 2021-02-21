class Solution {
public:
    int countPrimeSetBits(int L, int R) {
        const static vector<bool> mask = []() {
            vector<bool> mask(33);
            mask[0] = mask[1] = false;
            for (int i = 2; i < 33; ++i) {
                bool isPrime = true;
                for (int j = 2; j * j <= i; ++j) {
                    if (i % j == 0) {
                        isPrime = false;
                        break;
                    }
                }
                mask[i] = isPrime;
            }
            return mask;
        }();
        
        int total = 0;
        for (int i = L; i <= R; ++i) {
            int count = 0, v = i;
            while(v) {
                count += v%2;
                v /= 2;
            }
            if (mask[count]) {
                total++;
            }
        }
        
        return total;
    }
};
