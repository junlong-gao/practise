class Solution {
    vector<int> ss;
    string in;
    using ll = long long;
    const unordered_map<char, ll> opMap {
        {'+', -1},
        {'-', -2},
        {'*', -3},
        {'/', -4},
    };
    const unordered_map<ll, std::function<int(int, int)>> table {
        {-1, [&](int l, int r) { return l + r; } },
        {-2, [&](int l, int r) { return l - r; } },
        {-3, [&](int l, int r) { return l * r; } },
        {-4, [&](int l, int r) { return l / r; } }
    };
    
    int lh = 0;
    int eval() {
        vector<int> s;
        for (auto t : ss) {
          if (t >= 0) s.push_back(t);
          else {
            assert (s.size() >= 2);
            int r = s.back(); s.pop_back();
            int l = s.back(); s.pop_back();
            s.push_back(table.at(t)(l, r));
          }
        }
        assert(s.size() == 1);
        return s.back();
    }
    
    void num() {
        int cur = lh;
        while (lh < in.length() && std::isdigit(in[lh])) {
            lh++;
        }
        ss.push_back(stoi(in.substr(cur, lh - cur)));
    }
    
    void restFactor() {
        while (lh < in.length() &&
              (in[lh] == '*' || in[lh] == '/')) {
            char op = opMap.at(in[lh]); lh++; num();
            ss.push_back(op);
        }
    }
    
    void factor() {
        if (lh == in.length()) return;
        num();
        restFactor();
    }
    
    void restTerm() {
        while (lh < in.length() &&
              (in[lh] == '+' || in[lh] == '-')) {
            char op = opMap.at(in[lh]); lh++; factor();
            ss.push_back(op);
        }
    }
    
    void term() {
        factor();
        restTerm();
    }

public:
    int calculate(string s) {
       for (int i = 0; i < s.length(); ++i) {
           if (s[i] == ' ') {
               continue;
           } else {
               in.push_back(s[i]);
           }
       } 
        
       term(); return eval();
    }
};
