class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> v;
        for (auto e : nums) {
            v.push_back(to_string(e));
        }
        
        /*
        Normal sort should give lex largest, but here, the comp
        of the final result is by individual char, not by unit
        of the sort.
        */
        sort(v.begin(), v.end(), [](const string &l, const string &r){
           return l + r > r + l; 
        });
        
        if (v.front()[0] == '0') {
            return "0";
        }
        
        string ret;
        for (auto &r : v) {
            ret += r;
        }
        return ret;
    }
};