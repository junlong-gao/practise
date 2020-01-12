class Solution {
    int infty = INT_MAX / 2;
    unordered_map<char, pair<int, int>> table;
    int dist(char c1, char c2) {
        return abs(table[c1].first - table[c2].first) + abs(table[c1].second - table[c2].second);
    }
    vector<vector<vector<int>>> dp;
    int cost(const string w, int K, char c1, char c2) {
        if (K <= 1) return 0;
        if (dp[K][c1][c2] >= 0) return dp[K][c1][c2];
        int &ret = dp[K][c1][c2];
        if (c1 == w[K - 1]) {
            ret = min(
                cost(w, K - 1, w[K - 2], c2) + dist(w[K - 2], w[K - 1]),
                cost(w, K - 1, c1, w[K - 2]) + dist(w[K - 2], c2)
            );
            
            return ret;
        } else if (c2 == w[K - 1]) {
            ret = min(
                cost(w, K - 1, c1, w[K - 2]) + dist(w[K - 2], w[K - 1]),
                cost(w, K - 1, w[K - 2], c2) + dist(w[K - 2], c1)
            );
            
            return ret;
        } else {
            return ret = infty;
        }
    }
public:
    int minimumDistance(string word) {
        for (char c = 'A'; c <= 'Z'; ++c) {
            table[c] = make_pair((c - 'A') / 6, (c - 'A') % 6);
        }
        dp.resize(word.size() + 1,
                 vector<vector<int>>(256, vector<int>(256, -1)));
        int ret = infty;
        for (char c1 = 'A'; c1 <= 'Z'; ++c1) {
            for (char c2 = 'A'; c2 <= 'Z'; ++c2 ) {
                ret = min(ret, cost(word, word.size(), c1, c2));
            }
        }
        return ret;            
    }
};