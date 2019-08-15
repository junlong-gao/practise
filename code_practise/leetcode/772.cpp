class Solution {
  using ll = long long;
  string in;
  int lh;
  struct token {
     ll val;
     char op = 0;
     token (ll val_) : val(val_) {;}
     token (char op_) : op(op_) {;}
  };

  vector<token> tokens;
  const unordered_map<ll, std::function<ll(ll, ll)>> table {
    {'+', [&](ll l, ll r) { return l + r; } },
    {'-', [&](ll l, ll r) { return l - r; } },
    {'*', [&](ll l, ll r) { return l * r; } },
    {'/', [&](ll l, ll r) { return l / r; } }
  };

  void expr();

  void factor() {
    if (lh == in.size()) return;
    if (in[lh] == '(') {
      lh++; expr();
      assert(in[lh] == ')'); lh++;
    } else {
      ll sign = 1;
      if (in[lh] == '-') {
         sign = -1; lh++;
      }

      int cur = lh;
      while(lh < in.size() && isdigit(in[lh])) {
         lh++;
      }

      tokens.push_back(sign * stoll(in.substr(cur, lh - cur)));
    }
  }
  void restFactor() {
    while (lh < in.size() &&
            (in[lh] == '*' || in[lh] == '/')) {
       char op = in[lh]; lh++; factor();
       tokens.push_back(op);
    }
  }

  void term() {
    factor();
    restFactor();
  }

  void restTerm() {
    while (lh < in.size() &&
           (in[lh] == '+' || in[lh] == '-')) {
       char op = in[lh]; lh++; term();
       tokens.push_back(op);
    }
  }

  int eval() {
    vector<ll> s;
    for (auto t : tokens) {
      if (t.op == 0) s.push_back(t.val);
      else {
        assert (s.size() >= 2);
        int r = s.back(); s.pop_back();
        int l = s.back(); s.pop_back();
        s.push_back(table.at(t.op)(l, r));
      }
    }

    assert(s.size() == 1);
    return s.back();
  }

public:
  int calculate(string s) {
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != ' ') { in.push_back(s[i]); }
    }
    expr(); return eval();
  }
};

void Solution::expr() {
  term();
  restTerm();
}
