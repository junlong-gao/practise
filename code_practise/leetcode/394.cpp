class Solution {
    string build(const string &s, int &head) {
        if (head == s.size() || s[head] == ']') {
            return "";
        }
        string ret;
        if (isdigit(s[head])) {
            int tmp = head;
            while (isdigit(s[head])) {head++;}
            int rep = stoi(s.substr(tmp, head - tmp));
            assert(s[head] == '['); head++;
            string inter = build(s, head);
            assert(s[head] == ']'); head++;
            while (rep-->0) {
                ret += inter;
            }
            return ret + build(s, head);
        } else {
            assert(isalpha(s[head]));
            int tmp = head;
            while (head < s.size() && isalpha(s[head])) { head++; }
            string first = s.substr(tmp, head - tmp);
            return first + build(s, head); // do not put above line and and concat here: no order of evaluation of c++ expression
        }
    }
public:
    string decodeString(string s) {
        int head = 0;
        return build(s, head);
    }
};
