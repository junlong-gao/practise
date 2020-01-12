class Solution {
public:
    int minFlips(int a, int b, int c) {
        vector<int> av(64, 0), bv(64, 0), cv(64, 0);
        int mlength = 0;
        while (a || b || c) {
            av[mlength] = a % 2; a /= 2;
            bv[mlength] = b % 2; b /= 2;
            cv[mlength] = c % 2; c /= 2;
            mlength++;
        }
        assert(mlength <= 64);
        int count = 0;
        for (int i = 0; i < mlength; ++i) {
            if (cv[i] == 0) {
                if (av[i]) {count++;}
                if (bv[i]) {count++;}
            } else {
                if (av[i] == 0 && bv[i] == 0) {
                    count++;
                }
            }
        }
        return count;
    }
};