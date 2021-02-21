class Solution {
    map<string, int> parse(const string &str, int i, int j) {
        map<string, int> ret;
        if (i == j) {
            return ret;
        }
        
        int idx = i;
        while (idx < j) {
            if (str[idx] == '(') {
                int nextIdx = idx + 1;
                int open = 1;
                while (open > 0) {
                    if (str[nextIdx] == ')') open--;
                    if (str[nextIdx] == '(') open++;
                    nextIdx++;
                }
                auto sol = parse(str, idx + 1, nextIdx - 1);
                int count = 1;
                
                if (nextIdx < j && isdigit(str[nextIdx])) {
                    int tmp = nextIdx;
                    while (isdigit(str[nextIdx])) {
                        nextIdx++;
                    }
                    count = stoi(str.substr(tmp, nextIdx - tmp));
                }
                for (auto &pr : sol) {
                    ret[pr.first] += (pr.second * count);
                }
                idx = nextIdx;
            } else if (isupper(str[idx])) {
                int nextIdx = idx + 1;
                while (islower(str[nextIdx])) {
                    nextIdx++;
                }
                string atom = str.substr(idx, nextIdx - idx);
                int count = 1;
                
                if (nextIdx < j && isdigit(str[nextIdx])) {
                    int tmp = nextIdx;
                    while (isdigit(str[nextIdx])) {
                        nextIdx++;
                    }
                    count = stoi(str.substr(tmp, nextIdx - tmp));
                }
                ret[atom] += count;
                idx = nextIdx;
            }
        }
        return ret;
    }
public:
    string countOfAtoms(string formula) {
        auto res = parse(formula, 0, formula.size());
        string ret;
        for (auto &pr: res) {
            ret += pr.first;
            if (pr.second > 1) {
                ret += to_string(pr.second);
            }
        }
        
        return ret;
    }
};