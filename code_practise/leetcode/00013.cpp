class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> t {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        
        int i = 0;
        int ret = 0;
        while (i < s.size()) {
            if (i == s.size() - 1 || t[s[i]] >= t[s[i+1]]) {
                ret += t[s[i]]; i++;
            } else {
                ret += t[s[i + 1]] - t[s[i]]; i += 2;
            }
        }
        
        return ret;
    }
};
