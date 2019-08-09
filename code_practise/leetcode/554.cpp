class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int> px(wall.size());
        int best = wall.size();
        for (const auto &w : wall) {
            int x = 0;
            for (int i = 0; i < w.size() - 1; ++i) {
                x += w[i];
                px[x]++;
            }
        }
        for (auto &pr : px) {
            best = min(best, (int)wall.size() - pr.second);
        }
        return best;
    }
};
