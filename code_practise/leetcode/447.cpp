class Solution {
    using ll = unsigned long long;
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        auto dist= [&](const pair<int, int> l, const pair<int, int> r) {
           ll dx = l.first - r.first;
           ll dy = l.second - r.second;
            return dx * dx + dy * dy;
        };
        vector<unordered_map<ll, int>> iso(points.size());
        for (int i = 0; i < points.size(); ++i) {
            for (auto r : points) {
                iso[i][dist(points[i], r)]++;
            }
        }
        int ret = 0;
        for (auto & circles : iso) {
            for (auto & pr : circles) {
                if (pr.first == 0) continue;
                ret += pr.second * (pr.second - 1);
            }
        }
        return ret;
    }
};
