#include <iostream>
#include <regex>
#include <bits/stdc++.h>

using namespace std;

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
  
  vector<ll> tokens;
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
  
  void expr();
  void factor() {
    //if (lookahead == buf.size()) return;
    assert(lookahead < buf.size());
    if (buf[lookahead] == '(') {
      lookahead++;
      expr();
      //cout << lookahead << endl;
      assert(buf[lookahead] == ')');
      lookahead++;
    } else if (std::isdigit(buf[lookahead])){
      int cur = lookahead;
      assert(std::isdigit(buf[lookahead]));
      while(lookahead < buf.size() && std::isdigit(buf[lookahead])) {
        lookahead++;
      }
      tokens.push_back(std::stoll(buf.substr(cur, lookahead - cur)));
    }
  }
  void restFactor() {
    if (lookahead == buf.size() || 
        (buf[lookahead] != '*' && buf[lookahead] != '/')) return;
    char op = buf[lookahead];
    lookahead++;
    factor();
    tokens.push_back(opMap.at(op));
    restFactor();
  }
  
  void term() {
    assert(lookahead < buf.size());
    factor();
    restFactor();
  }
  
  void restTerm() {
    if (lookahead == buf.size() || 
        (buf[lookahead] != '+' && buf[lookahead] != '-')) return;
    char op = buf[lookahead];
    lookahead++;
    term();
    tokens.push_back(opMap.at(op));
    restTerm();
  }
  
  int eval() {
    vector<int> s;
    for (auto t : tokens) {
      if (t >= 0) s.push_back(t);
      else {
        assert (s.size() >= 2);
        int second = s.back(); s.pop_back();
        int first = s.back(); s.pop_back();
        s.push_back(table.at(t)(first, second));
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
  restTerm();
}

void ASSERT(int a, int b) {
  if (a == b) return;
  cout << "Assertion fail: expect " << a << " got " << b << endl;
  assert(0);
}


int main() {
  unordered_map<string, int> ts{
    {"1 +2", 3},
    {"(6 +2) *(8 - 7)", 8},
    {"6 +1 *(98 - 7)", 97},
    {"(6 - 11) / (5 - 3)", -2},
    {"(6 - 11) / (3 - 5)", 2},
    {"(2 - (2 - 3) * 5)", 7},
    {"(2+6* 3+5- (3*14/7+2)*5)+3", -12},
    {"0-2147483648", 2147483648}
  };
  
  for (auto t : ts) {
    Solution s;
    ASSERT(t.second, s.calculate(t.first));
  }
  cout << "...Passed" << endl;
}
