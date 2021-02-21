class Solution {
public:
    bool isIsomorphic(string s, string t) {
        auto inject = [&](string &s, vector<int> &table) {
            int id = 0;
            unordered_map<char, int> m;
            for (auto c : s) {
                if (m.count(c) == 0) {
                    m[c] = id++;
                }
                table.push_back(m[c]);
            }
        };
        vector<int> s1, s2;
        inject(s, s1); inject(t, s2);
        return s1 == s2;
    }
};
