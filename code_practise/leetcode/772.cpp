class Solution {
    struct ent_t {
        char op;
        int oprand;
        bool isOp;
        bool isLeftOpen;
        bool isRightOpen;
    };
    
    vector<ent_t> parse(const string &s) {
        int i = 0;
        vector<ent_t> ret;
        while (i < s.size()) {
            while (i < s.size() && s[i] == ' ') {
                i++;
            }
            if (i == s.size()) {
                break;
            }
            int j = i;
            if (isdigit(s[j])) {
                while (j < s.size() && isdigit(s[j])) {
                    j++;
                }
                ret.push_back(ent_t{0, stoi(s.substr(i, j - i)),
                                   false, false, false});
                i = j;
            } else {
                if (s[j] == ')') {
                    ret.push_back(ent_t{0, 0, false, false, true});
                } else if (s[j] == '(') {
                    ret.push_back(ent_t{0, 0, false, true, false});
                } else {
                    ret.push_back(ent_t{s[j], 0, true, false, false});
                }
                i = j + 1;
            }
        }
        
        return ret;
    }
    /*
    if it is an op or left open: push it to the stack
    if it is a number:
        eval the number with the stack:
           assert stack top is an op
           if the op is + or -:
              save the number with sign for future use
           else
              eval the number with the op and the next element in the stack
    if it is a right: sum to the left open, treat this sum as a new number and
    eval it with the remaining stack
    */
public:
    int calculate(string str) {
        vector<ent_t> s; // only number or left open or + or -
        auto tokens = parse(str);
        
        if (tokens.empty()) {
            return 0;
        }
        
        auto eval = [&s](ent_t t) {
            if (s.size() == 0 || s.back().isLeftOpen) {
                s.push_back(t);
            } else {
                assert(s.back().isOp);
                if (s.back().op == '+') {
                    s.push_back(t);
                } else if (s.back().op == '-') {
                    t.oprand = 0 - t.oprand;
                    s.push_back(t);
                } else if (s.back().op == '*') {
                    s.pop_back();
                    int prev = s.back().oprand; s.pop_back();
                    s.push_back(ent_t{0, prev * t.oprand, false, false, false});
                } else if (s.back().op == '/') {
                    s.pop_back();
                    int prev = s.back().oprand; s.pop_back();
                    s.push_back(ent_t{0, prev / t.oprand, false, false, false});
                }
            }
        }; 
        
        for (int i = 0; i < tokens.size(); ++i) {
            auto &t = tokens[i];
            if (t.isOp || t.isLeftOpen) {
                s.push_back(t);
            } else if (t.isRightOpen) {
                int sum = 0;
                while (!s.back().isLeftOpen) {
                    auto v = s.back(); s.pop_back();
                    if (v.isOp) {
                        assert(v.op == '+' || v.op == '-');
                        continue;
                    }
                    assert(!v.isLeftOpen && !v.isRightOpen);
                    sum += v.oprand; 
                }
                
                if (!s.empty()) {
                    assert(s.back().isLeftOpen);
                    s.pop_back();
                }
                
                ent_t tt = ent_t{0, sum, false, false, false};
                eval(tt);
            } else {
                eval(t);
            }
        }
        
        int ret = 0;
        while (s.size()) {
            if (!s.back().isOp) {
                ret += s.back().oprand;
            }
            s.pop_back();
        }
        
        return ret;
    }
};