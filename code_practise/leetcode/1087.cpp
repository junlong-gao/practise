class Solution {
    int lh = 0;
    vector<string> helper(const string &S) {
        vector<string> options;
        if (lh == S.length()) return {""};
        if (S[lh] == '{') {
            lh++;
            for (int cur = lh; S[lh - 1] != '}'; ++lh) {
                if (S[lh] == ',' || S[lh] == '}') {
                    options.push_back(S.substr(cur, lh - cur));
                    cur = lh + 1;
                }
            }
        } else {
            int cur = lh;
            while (lh < S.length() && S[lh] != '{') {
               lh++;
            }
            options.push_back(S.substr(cur, lh - cur));
        }
        vector<string> ret;
        for (auto &s : helper(S)) {
            for (auto &l : options) {
               ret.push_back(l + s);
            }
        }
        return ret;
    }
public:
    vector<string> expand(string S) {
        lh = 0;
        auto r = helper(S);
        sort(r.begin(), r.end());
        return r;
    }
};
