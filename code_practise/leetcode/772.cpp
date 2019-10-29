class Solution {
  using ll = long long;
  string buf;
  int lookahead;
  void removeSpace() {
    string t;
    for (int i = 0; i < buf.size(); ++i) {
      if (buf[i] != ' ') {
        t.push_back(buf[i]);
      }
    }
    swap(buf, t);
  }
  
  struct token_t {
    bool isNum;
    ll val;
  };
  
  vector<token_t> tokens;
  const unordered_map<char, ll> opMap {
    {'+', -1},
    {'-', -2},
    {'*', -3},
    {'/', -4},
  };
  const unordered_map<ll, std::function<ll(ll, ll)>> table {
    {-1, [&](ll l, ll r) { return l + r; } },
    {-2, [&](ll l, ll r) { return l - r; } },
    {-3, [&](ll l, ll r) { return l * r; } },
    {-4, [&](ll l, ll r) { return l / r; } }
  };
  
  void expr();
  void factor() {
    assert(lookahead < buf.size());
    if (buf[lookahead] == '(') {
      lookahead++;
      expr();
        
      assert(buf[lookahead] == ')');
      lookahead++;
    } else {
      int cur = lookahead;
      if (!std::isdigit(buf[lookahead])) {
          assert(buf[lookahead++] == '-');
      }
      assert(std::isdigit(buf[lookahead]));
      while(lookahead < buf.size() && std::isdigit(buf[lookahead])) {
        lookahead++;
      }
      tokens.push_back(token_t{true, std::stoll(buf.substr(cur, lookahead - cur))});
    }
  }
    
  void restTerm() {
     if (lookahead != buf.size() && buf[lookahead] == '*') {
        char op = buf[lookahead++];
        factor();
        tokens.push_back(token_t{false, opMap.at(op)});
        restTerm();     
     } else if (lookahead != buf.size() && buf[lookahead] == '/') {
        char op = buf[lookahead++];
        factor();
        tokens.push_back(token_t{false, opMap.at(op)});
        restTerm();
     } else {
        // empty production
        return;
     }
  }
  
  void term() {
    assert(lookahead < buf.size());
    factor();
    restTerm();
  }
  
  void restExpr() {
    if (lookahead != buf.size() && buf[lookahead] == '+') {
        char op = buf[lookahead++];
        term();
        tokens.push_back(token_t{false, opMap.at(op)});
        restExpr();
    } else if (lookahead != buf.size() && buf[lookahead] == '-') {
        char op = buf[lookahead++];
        term();
        tokens.push_back(token_t{false, opMap.at(op)});
        restExpr();
    } else {
        // empty production
        return;
    }
  }
  
  int eval() {
    vector<int> s;
    for (auto t : tokens) {
      if (t.isNum) s.push_back(t.val);
      else {
        assert (s.size() >= 2);
        int second = s.back(); s.pop_back();
        int first = s.back(); s.pop_back();
        s.push_back(table.at(t.val)(first, second));
      }
    }
    assert(s.size() == 1);
    return s.back();
  }
  
public:
  int calculate(string s) {
    lookahead = 0;
    swap(s, buf);
    removeSpace();
    expr();
    return eval();
  }
};

void Solution::expr() {
  if (lookahead == buf.size()) return;
  term();
  restExpr();
}

