class Solution {
public:
    bool isValid(string s) {
        vector<char> b;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ')') {
                if (b.empty() || b.back() != '(') {
                    return false;
                }
                b.pop_back();
            } else if (s[i] == ']') {
                if (b.empty() || b.back() != '[') {
                    return false;
                }
                b.pop_back();
            } else if (s[i] == '}') {
                if (b.empty() || b.back() != '{') {
                    return false;
                }
                b.pop_back();
            } else {
                if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                    b.push_back(s[i]);
                }
            }
        }
        if (b.empty()) {
            return true;
        }
        return false;
    }
};
