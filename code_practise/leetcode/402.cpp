class Solution {
public:
    string removeKdigits(string num, int k) {
        vector<char> s;
        for (int i = 0; i < num.size(); ++i) {
            while(!s.empty() && (s.back() > num[i] && k > 0)) {
                k--;
                s.pop_back();
            }
            s.push_back(num[i]);
        }
        int start = 0;
        for (; start < s.size() && s[start] == '0'; ++start) {
            ;
        }
        if (start + k >= s.size()) return "0";
        string ret;
        for (int i = start; i + k < s.size(); ++i) {
            ret += s[i];
        }
        return ret;
    }
};
