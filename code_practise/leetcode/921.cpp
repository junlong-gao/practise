class Solution {
public:
    int minAddToMakeValid(string S) {
        vector<bool> s;
        int ret = 0;
        for (int i = 0; i < S.size(); ++i) {
            if (S[i] == '(') {
                s.push_back(true);
            } else {
                if (s.empty()) {
                    ret++;
                } else {
                    s.pop_back();
                }
            }
        }
        
        return s.size() + ret;
    }
};
