class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> left;
        vector<int> dp(s.size() + 1, 0);
        int ret = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                left.push_back(i);
                dp[i] = 0;
            } else {
                if (left.empty()) {
                    dp[i] = 0;
                } else {
                    if (left.back() == 0) {
                        dp[i] = i + 1;
                    } else {
                        dp[i] = dp[left.back() - 1] + i - left.back() + 1;
                    }
                    left.pop_back();
                }
            }
            ret = max(ret, dp[i]);
        }
        return ret;
    }
};
