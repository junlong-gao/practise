/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        if (points.empty()) return 0;
        int best = INT_MIN;
        for (int i = 0; i < points.size(); ++i) {
            int same = 0, ver = 0, cur = INT_MIN;
            map<pair<int, int>, int> ks;
            int x = points[i].x, y = points[i].y;
            for (int j = i + 1; j < points.size(); ++j) {
                int dx = points[j].x - x, dy = points[j].y - y;
                if (dx == 0 && dy == 0) {
                    same++; continue;
                } else if (dx == 0) {
                    ver++; continue;
                } else {
                    int gcd = __gcd(dx, dy);
                    dx = dx / gcd;
                    dy = dy / gcd;
                    cur = max(cur, ++ks[make_pair(dx, dy)]);
                }
            }
            cur = max(cur, ver);
            best = max(best, cur + same + 1);
        }
        return best;
    }
};