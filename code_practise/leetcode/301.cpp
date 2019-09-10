/*
brute force: try out all possible removal to make it valid.
- how to enumerate all possiblities? key insight: for all possible removal,
  if it is the minimal removal, it must be removing exactly a fix amount of
  left and right parenthes.
- backtrace: for every state, we need to determine how many extra left/right
  parenthes to remove, and which char we are deciding to keep or remove.
- if we have l left parenthes to remove (l > 0) and the current char is '(' and
  the previous constructed string ends with '(', there is no point to consider 
  the states removing the current '(', they will be considered again by the removal
  of the previous '(' and keeping the current '('.
*/
class Solution {
    void search(int pl, int pr, int l, int r, int idx, string& sofar, const string s,
                vector<string> &ret) {
        if (idx == s.size()) {
            if (l || r || (pl != pr)) return;
            ret.push_back(sofar);
            return;
        }
        
        if (pl < pr) return;
        if (s[idx] == '(') {
            sofar.push_back('(');
            search(pl + 1, pr, l, r, idx + 1, sofar, s, ret);
            sofar.pop_back();
            if (l && (sofar.empty() || sofar.back() != '(')) {
                search(pl, pr, l - 1, r, idx + 1, sofar, s, ret);
            }
        } else if (s[idx] == ')') {
            sofar.push_back(')');
            search(pl, pr+1, l, r, idx + 1, sofar, s, ret);
            sofar.pop_back();
            if (r && (sofar.empty() || sofar.back() != ')')) {
                search(pl, pr, l, r - 1, idx + 1, sofar, s, ret);
            }
        } else {
            sofar.push_back(s[idx]);
            search(pl, pr, l, r, idx + 1, sofar, s, ret);
            sofar.pop_back();
        }
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        int l = 0, r = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                l++;
            } else if (s[i] == ')') {
                if (l == 0) {
                    r++;
                } else {
                    l--;
                }
            }
        }
        vector<string> ret;
        string t;
        search(0, 0, l, r, 0, t, s, ret);
        return ret;
    }
};
