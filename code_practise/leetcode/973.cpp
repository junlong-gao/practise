class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        auto c = [&](int l, int r) {
            long long d1 = points[l][0] * points[l][0] +
                                points[l][1] * points[l][1];
            long long d2 = points[r][0] * points[r][0] +
                                points[r][1] * points[r][1];
            
            if (d1 != d2) return d1 < d2;
            return l < r;
        };
        set<int, decltype(c)> bag(c);
        for (int i = 0; i < points.size(); ++i) {
            bag.insert(i);
        }
        
        vector<vector<int>> ret;
        while (K-->0 && bag.size()) {
            ret.push_back(points[*bag.begin()]);
            bag.erase(bag.begin());
        }
        
        return ret;
    }
};
