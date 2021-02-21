class Solution {
    void gen(string &sofar, int left, int n, vector<string> *output) {
        if (sofar.size() == 2 * n) {
            output->push_back(sofar);
            return;
        } else {
            char last = 0;
            if (sofar.size()) {
                last = sofar.back();
            }
            if (left < n) {
                sofar.push_back('(');
                gen(sofar, left + 1, n, output);
                sofar.pop_back();
            }
            
            if (sofar.size() - left < left) {
                sofar.push_back(')');
                gen(sofar, left, n, output);
                sofar.pop_back();
            }
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> output;
        string t;
        gen(t, 0, n, &output);
        return output;
    }
};