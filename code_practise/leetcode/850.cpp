class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        vector<vector<int>> &rec = rectangles;
        int n = rec.size();
        vector<int> fx(2*n + 1, 0), fy(2*n + 1, 0);
        for (int i = 0; i < n; ++i) {
            fx[2*i]     = rec[i][0];
            fx[2*i+1]   = rec[i][2];
            fy[2*i]     = rec[i][1];
            fy[2*i + 1] = rec[i][3];
        }
        sort(fx.begin(), fx.end());
        sort(fy.begin(), fy.end());
        unsigned long long ans = 0, M = 1e9 + 7;
        for (int i = 1; i < 2*n + 1; ++i) {
            for (int j = 1; j < 2*n + 1; ++j) {
                for (auto & r : rec) {
                    if (fx[i - 1] >= r[0] &&
                        fx[i]     <= r[2] &&
                        fy[j - 1] >= r[1] &&
                        fy[j]     <= r[3]) {
                        unsigned long long dx = fx[i] - fx[i - 1];
                        unsigned long long dy = fy[j] - fy[j - 1];
                        ans = (ans + (dx * dy) % M) % M;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};
