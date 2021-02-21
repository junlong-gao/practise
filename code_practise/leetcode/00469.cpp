class Solution {
public:
    bool isConvex(vector<vector<int>>& points) {
        auto cross = [&](vector<int> &a, vector<int> &b, vector<int> &c) {
            int lx = b[0] - a[0];
            int ly = b[1] - a[1];
            int rx = c[0] - b[0];
            int ry = c[1] - b[1];
            return (lx * ry) - (ly * rx);
        };
        
        int n = points.size();
        
        sort(points.begin(), points.end(), [&](const vector<int> &l, const vector<int> &r){
            if (l[0] != r[0]) return l[0] < r[0];
            return l[1] < r[1];
        });
        
        vector<int> cons (2 * n); int k = 0;
        for (int i = 0; i < n; ++i) {
            while (k > 1 && (cross(points[cons[k - 2]], points[cons[k - 1]], points[i])) < 0) k--;
            cons[k++] = i;
        }
        
        for (int i = n - 2, t = k; i >= 0; --i) {
            while (k > t && (cross(points[cons[k - 2]], points[cons[k - 1]], points[i])) < 0) k--;
            cons[k++] = i;
        }
        cons.resize(k);
        // the constructed convex hull is itself
        unordered_set<int> counter;
        for (auto idx : cons) {
            counter.insert(idx);
        }
        return counter.size() == n;
    }
};
