class Solution {
    vector<int> dp;
    int search(const string &s, int idx) {
        if (idx == s.size()) {
            return 1;
        }
        int &ret = dp[idx];
        if (ret != -1) {
            return ret;
        }
        
        ret = 0;
        if (s[idx] == '0') {
            return ret = 0;
        }
        
        // 1 digit
        if (s[idx] >= '1' && s[idx] <= '9') {
            ret += search(s, idx + 1);
        }
        
        if (idx + 1 == s.size()) {
            return ret;
        }
        
        if ((s[idx] == '1' && s[idx + 1] >= '0' && s[idx + 1] <= '9') ||
            (s[idx] == '2' && s[idx + 1] >= '0' && s[idx + 1] <= '6')) {
            ret += search(s, idx + 2);
        }
        
        return ret;
    }
public:
    int numDecodings(string s) {
       dp.resize(s.size(), -1);
        return search(s, 0);
    }
};