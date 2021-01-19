class Solution {
public:
    void reverseWords(vector<char>& s) {
        int i = 0;
        while(i < s.size()) {
            int j = i;
            while (j < s.size() && s[j] != ' ') {
                j++;
            }
            for (int k = i, l = j - 1; k < l; ++k, --l) {
                swap(s[k], s[l]);
            }
            i = j + 1;
        }
        for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
            swap(s[i], s[j]);
        }
    }
};
