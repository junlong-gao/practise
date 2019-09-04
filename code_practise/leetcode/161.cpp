class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if (abs((int)s.size() - (int)t.size()) > 1 || s == t) return false;
        if (s.size() > t.size()) swap(s, t);
        
        int i = 0;
        while (i < s.size() && s[i] == t[i]) {
            i++;
        }
        
        if (i == s.size()) return s.size() < t.size();
        if (s.size() == t.size()) {
            i++;
            while (i < s.size()) {
                if (s[i] != t[i]) return false;
                i++;
            }
            return true;
        } else {
            while(i < s.size()) {
                if (s[i] != t[i + 1]) return false;
                i++;
            }
            return true;
        }
    }
};
