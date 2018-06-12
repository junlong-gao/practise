class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> f;
        for (auto char c : s) {
            f[c]++;
        }
        sort(s.begin(), s.end(), [&](const char l, const char r) {
            return f[l] > f[r];
        });
        return s;
    }
};
