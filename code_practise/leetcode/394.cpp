class Solution {
    
    string decode(int& start, string& s) {
        if (start == s.size() || s[start] == ']') {
            return "";
        } else if (std::isdigit(s[start])) {
            int cur = start;
            while (start < s.size() && std::isdigit(s[start])) {
                start++;
            }
            int n_rep = stoi(s.substr(cur, start - cur));
            assert(s[start] == '['); start++;
            string temp = decode(start, s);
            assert(s[start] == ']'); start++;
                
            string ret;
            for (int i = 0; i < n_rep; ++i) {
                ret += temp;
            }
            return ret + decode(start, s);
        } else {
            int cur = start; assert(std::isalpha(s[start]));
            while (start < s.size() && std::isalpha(s[start])) {
                start++;
            }
            string t = s.substr(cur, start - cur);
            return  t + decode(start, s);
            // return s.substr(cur, start - cur) + decode(start, s); is wrong. Why?
        }
    }
public:
    string decodeString(string s) {
        int start = 0;
        return decode(start, s);
    }
};
