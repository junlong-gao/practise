/*

expr -> term restTerm
     |  eps
     
term -> number { push number }
     | (expr)
     
restTerm -> + term {push op +} restTerm
         |  - term {push op -} restTerm
         |  eps
*/

class Solution {
    int lookahead;
    string input;
    struct token {
        bool isOp;
        char op;
        int oprand;
    };
    vector<token> semanticStack;

    void expr();
    void term() {        
        if (input[lookahead] == '(') {
            lookahead++;
            expr();
            
            assert(input[lookahead] == ')'); lookahead++;
        } else {
            int cur = lookahead;
            while (lookahead < input.size() &&
                      std::isdigit(input[lookahead])) {
                lookahead++;
            }
            int v = stoi(input.substr(cur, lookahead - cur));
            semanticStack.push_back({false, 0, v});
        }
    }
    void restTerm() {        
        if (lookahead < input.size() &&
            (input[lookahead] == '+' || input[lookahead] == '-')) { 
            char op = input[lookahead]; lookahead++;
            
            term();
            semanticStack.push_back({true, op, 0});
            
            restTerm();
        } else {
            ; // eps
        }
    }

    int eval() {
        vector<int> s;
        if (semanticStack.empty()) return 0;
        for (auto &token : semanticStack) {
            if (!token.isOp) {
                s.push_back(token.oprand);
            } else {
                assert(s.size() >= 2);
                int op2 = s.back(); s.pop_back();
                int op1 = s.back(); s.pop_back();
                s.push_back(token.op == '+' ? op1 + op2 : op1 - op2);
            }
        }
        
        return s.back();
    }
public:
    int calculate(string s) {
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == ' ') {
                continue;
            } else {
                input.push_back(s[i]);
            }
        }
        
        lookahead = 0;
        expr();
        return eval();
    }
};

void Solution::expr() {
    if (lookahead < input.size()) {
        term();
        restTerm();
    } else {
        ;//eps
    }
}
