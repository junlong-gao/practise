/*
A = ...x...y...
B = ...y...x...

xy < yx => A < B

*/

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [&](int l, int r){
            return to_string(r) + to_string(l) < to_string(l) + to_string(r);
        });
        string init {""};
        for (auto e : nums) {
            init += to_string(e);
        }
        int buf = 0;
        for (int i = 0; i < init.length(); ++i) {
            if (init[i] == '0') buf++;
            else break;
        }
        if (buf == init.length()) return "0";
        return init.substr(buf, init.length() - buf);
    }
};