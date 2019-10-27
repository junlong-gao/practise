class Solution {
    int lh = 0;
    set<string> expr(const string& S);
    set<string> Rexpr(const string& S) {
        if (lh == S.length() || S[lh] == ',' || S[lh] == '}') return {""};
        return expr(S);
    }
    
    set<string> comma(const string& S) {
        auto first = expr(S);
        auto second = Rcomma(S);
        for (auto& s : second) {
            first.insert(s);
        }
        return first;
    }
    set<string> Rcomma(const string& S) {
        if (lh == S.length() || S[lh] == '}') return {};
        assert(S[lh] == ','); lh++;
        return comma(S);
    }
public:
    vector<string> braceExpansionII(string expression) {
        auto r = expr(expression);
        return {r.begin(), r.end()};
    }
};

set<string> Solution::expr(const string& S)
{
    set<string> opt;
    if (S[lh] == '{') {
        lh++;
        opt = comma(S);
        assert(S[lh]=='}');
        lh++;
    } else {
        int cur = lh;
        while (isalpha(S[lh])) {
            lh++;
        }
        opt.insert(S.substr(cur, lh - cur));
    }

    set<string> ret;
    auto rest = Rexpr(S);
    for (auto& f : opt) {
        for (auto& l : rest) {
            ret.insert(f + l);
        }
    }
    return ret;
}
