/*

encoded = expr # pop # encoded # pop, concat, push
               |  expr

expr = <literal> # push literal
         | <number> [ encoded ] # pop, repeat for number times, push

literal -> alphabets
number -> digit*


example:
3[a2[c]]
accaccacc
*/

class Solution {
  int lookahead = 0;
  string str;
  vector<string> stack;
  void encoded();
  void expr() {
    assert(lookahead != str.size());
    if (!std::isdigit(str[lookahead])) {
      string v;
      while (lookahead < str.size() &&
             (std::islower(str[lookahead]) || std::isupper(str[lookahead]))) {
        v.push_back(str[lookahead++]);
      }
      stack.push_back(v);
      return;
    } else {
      string rep;
      while (std::isdigit(str[lookahead])) {
        rep.push_back(str[lookahead++]);
      }
      int n_rep = stoi(rep);

      assert(str[lookahead] == '[');
      lookahead++;

      encoded();
      assert(str[lookahead] == ']');
      lookahead++;
      string output = std::move(stack.back());
      stack.back() = "";
      for (int i = 0; i < n_rep; ++i) {
        stack.back() += output;
      }
    }
  }

 public:
  string decodeString(string s) {
    str = std::move(s);
    lookahead = 0;
    encoded();
    return stack.back();
  }
};

void Solution::encoded() {
  if (lookahead == str.size() || str[lookahead] == ']') {
    stack.push_back("");
    return;
  }

  expr();
  string out1 = std::move(stack.back());
  stack.pop_back();

  encoded();
  string out2 = std::move(stack.back());
  stack.pop_back();

  stack.push_back(out1 + out2);
  return;
}

/*
aa

3[aa]

bb3[cc]

a3[4[b5[d]]] ->
abdddddbdddddbdddddbdddddbdddddbdddddbdddddbdddddbdddddbdddddbdddddbddddd


*/
