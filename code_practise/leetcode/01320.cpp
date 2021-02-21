auto f = []() {
    std::ios::sync_with_stdio(false);cin.tie(NULL); return 0;
}();

class Solution {
    int dist(char c1, char c2) {
        int xc1 = c1 / 6; int yc1 = c1 % 6;
        int xc2 = c2 / 6; int yc2 = c2 % 6;
        return abs(xc1 - xc2) + abs(yc1 - yc2);
    }
    
public:
    int minimumDistance(string word) {
        array<array<int, 26>, 2> dp;

        int ret = INT_MAX;
        for (int i = 0; i < word.size(); ++i) {
            for (int c = 0; c < 26; ++c) {
                if (i == 0) { dp[i][c] = 0; continue; }
                dp[i & 1][c] = min(dp[(i + 1) & 1][c] + dist(word[i - 1] - 'A', word[i] - 'A'),
                               dp[(i + 1) & 1][word[i] - 'A'] + dist(word[i - 1] - 'A', c));
                if (i == word.size() - 1) {
                    ret = min(ret, dp[i & 1][c]);
                }
            }
        }

        return ret;            
    }
};