/*
expr -> { comma } expr
      |  literal expr
      |  eps <{""}>
      
comma -> expr Rcomma
Rcomma -> , comma
       | eps <{}>
*/
class Solution {
    int lh = 0;
    set<string> expr(const string& S);
    
    set<string> comma(const string& S) {
        //cout << "comma " << lh << endl;

        auto first = expr(S);
        auto second = Rcomma(S);
        for (auto& s : second) {
            first.insert(s);
        }
        return first;
    }
    set<string> Rcomma(const string& S) {
        //cout << "Rcomma " << lh << endl;

        if (S[lh] == ',') {
            assert(S[lh] == ','); lh++;
            return comma(S);
        } else {
            return {};
        }
    }
public:
    vector<string> braceExpansionII(string expression) {
        auto r = expr(expression);
        return {r.begin(), r.end()};
    }
};

set<string> Solution::expr(const string& S)
{
    //cout << "expr " << lh << endl;
    set<string> opt;
    if (lh < S.length() && S[lh] == '{') {
        lh++;
        opt = comma(S);
        assert(S[lh]=='}');
        lh++;
    } else if (lh < S.length() && isalpha(S[lh])){
        int cur = lh;
        while (isalpha(S[lh])) {
            lh++;
        }
        opt.insert(S.substr(cur, lh - cur));
    } else {
        // eps
        return {""};
    }

    set<string> ret;
    auto rest = expr(S);
    for (auto& f : opt) {
        for (auto& l : rest) {
            ret.insert(f + l);
        }
    }
    return ret;
}
