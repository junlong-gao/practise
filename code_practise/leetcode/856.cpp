class Solution {
    int lookahead;
    vector<char> s;
    string buf;
    void expr();
    void factor() {
        if (lookahead == buf.length() || buf[lookahead] != '(') {
            s.push_back(1);
            return;
        }
        expr();
    }
    
    int eval() {
        vector<int> tmp;
        for (auto token : s) {
            if (token == '+') {
                auto op1 = tmp.back(); tmp.pop_back();
                auto op2 = tmp.back(); tmp.pop_back();
                tmp.push_back(op1 + op2);
            } else if (token == '2') {
                tmp.back() *= 2;
            } else {
                tmp.push_back(1);
            }
        }
        return tmp.back();
    }
public:
    int scoreOfParentheses(string S) {
        if (S.empty()) return 0;
        lookahead = 0; swap(buf, S);
        expr();
        return eval() / 2;
    }
};

void Solution::expr() {
   lookahead++; // (
   factor();
   lookahead++; // )
   s.push_back('2');
   if (lookahead == buf.length() || buf[lookahead] != '(') {
       return;
   }
   expr();
   s.push_back('+');
}

/*
"(()(()))"
1 2 1 2 2 + 2


*/