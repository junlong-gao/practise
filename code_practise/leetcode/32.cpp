class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> dp(s.length() + 1, 0);
        int best = 0;
        for (int i = 1; i < s.length(); ++i) {
            if (i == 1) {
                dp[i] = (s[i] == ')' && s[i-1] == '(') ? 2 : 0;
            } else {
                // s[0..i] has at least 3 elements.
                if (s[i] == '(') {
                    continue;
                }

                if (s[i-1] == ')') {
                    // ... (...))
                    int pivit = i-1-dp[i-1];
                    if (pivit < 0) {
                        continue;
                    }
                    if (s[pivit] == ')') {
                        continue;
                    }
                    dp[i] = 2 + dp[i-1] + (pivit > 0 ? dp[pivit - 1] : 0);
                } else {
                    // ... ()
                    dp[i] = 2 + dp[i-2];
                }
            }
            best = max(best, dp[i]);
        }
        return best;
    }
};
