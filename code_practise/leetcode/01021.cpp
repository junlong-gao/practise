class Solution {
public:
    string removeOuterParentheses(string S) {
        int c = 0;
        string ret;
        for (int i = 0; i < S.size(); ++i) {
            if (S[i] == '(') {
                if (c > 0) {
                    ret.push_back(S[i]);
                }
                c++;
            } else {
                c--;
                if (c > 0) {
                    ret.push_back(S[i]);
                }
            }
        }
        return ret;
    }
};
