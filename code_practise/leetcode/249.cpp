class Solution {
    string canonicalForm(const string &s) {
        int shift = s[0] - 'a';
        string ret;
        for (int i = 0; i < s.size(); ++i) {
            ret.push_back('a' + (s[i] - 'a' - shift + 26) % 26);
        }
        return ret;
    }
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> bag;
        for (const auto & str : strings) {
            bag[canonicalForm(str)].push_back(str);
        }
        
        vector<vector<string>> ret;
        for (auto & bucket : bag) {
            if (bucket.second.size()) {
                ret.emplace_back(move(bucket.second));
            }
        }
        
        return ret;
    }
};