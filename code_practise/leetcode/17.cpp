class Solution {
    unordered_map<int,string> d2c {
        {2, "abc"},
        {3, "def"},
        {4, "ghi"},
        {5, "jkl"},
        {6, "mno"},
        {7, "pqrs"},
        {8, "tuv"},
        {9, "wxyz"}
    };
    void search(string &s, int idx, string &sofar, vector<string> *output) {
        if (idx == s.size()) {
            output->push_back(sofar);
            return;
        }
        for (auto c : d2c[s[idx] - '0']) {
            sofar.push_back(c);
            search(s, idx + 1, sofar, output);
            sofar.pop_back();
        }
        return;
    }
public:
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) {
            return {};
        }
        vector<string> ret;
        string sofar;
        search(digits, 0, sofar, &ret);
        return ret;
    }
};
