class Solution {
    vector<int> dfs(const string& in, int s, int e) {
        if (s == e) return {};
        vector<int> ret;
        for (int i = s; i < e; ++i) {
            if (std::isdigit(in[i])) {
                continue;
            }
            vector<int> l = dfs(in, s, i);
            vector<int> r = dfs(in, i + 1, e);
            for (auto lv : l) { for (auto rv : r) {
                ret.push_back([&](){
                    if (in[i] == '+') {  return lv + rv; }
                    else if (in[i] == '-') { return lv - rv; } 
                    else if (in[i] == '*') { return lv * rv; }
                    assert(0);
                }());
            }}
        }
        
        if (ret.empty()) {
            return {stoi(in.substr(s, e - s))};
        } else {
            return ret;
        }
    }
public:
    vector<int> diffWaysToCompute(string input) {
        return dfs(input, 0, input.length());
    }
};
