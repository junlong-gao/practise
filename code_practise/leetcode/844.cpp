class Solution {

public:
    bool backspaceCompare(string S, string T) {
        int i = S.size() - 1, j = T.size() - 1;
        int Sb = 0, Tb = 0;
        while (i >= 0 && j >= 0) {
            while (i >= 0 && (Sb || S[i] == '#')) {
                if (S[i] == '#') {
                    Sb++;
                } else {
                    Sb--;
                }
                i--;
            }
            while (j >= 0 && (Tb || T[j] == '#')) {
                if (T[j] == '#') {
                    Tb++;
                } else {
                    Tb--;
                }
                j--;
            }
            if (i >= 0 && j >= 0) {
                if (S[i] != T[j]) return false;
                i--; j--;
            }
        }
        return i < 0 && j < 0;
    }
};
