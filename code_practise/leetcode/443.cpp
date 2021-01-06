class Solution {
public:
    int compress(vector<char>& chars) {
        int i = 0; int j = 0;
        while (j < chars.size()) {
            int k = j + 1;
            while (k < chars.size() && chars[k] == chars[j]) { k++; }
            chars[i] = chars[j];
            i++;
            if (k - j > 1) {
                string t = to_string(k - j);
                for (int l = 0; l < t.size(); ++l, ++i) {
                    chars[i] = t[l];
                }
            }
            j = k;
        }
        return i;
    }
};
