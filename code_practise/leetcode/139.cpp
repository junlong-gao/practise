class Solution {
    unordered_map<int, bool> dp;
    bool breaker(string &s, int i, unordered_set<string> &bag) {
        if (dp.count(i) == 1) {
            return dp[i];
        }
        if (i == s.size()) {
            return true;
        }
        for (int j = i + 1; j <= s.size(); ++j) {
            if (bag.count(s.substr(i, j - i)) == 1 && breaker(s, j, bag)) {
                return dp[i] = true;
            }
        }
        return dp[i] = false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> bag;
        for (const auto & w : wordDict) {
            bag.insert(w);
        }
        return breaker(s, 0, bag);
    }
};
