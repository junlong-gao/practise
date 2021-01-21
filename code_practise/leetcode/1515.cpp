class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        auto dist = [&positions](double x, double y) {
            double ret = 0;
            for (auto &p:positions) {
                ret += hypot(p[0] - x, p[1] - y);
            }
            return ret;
        };
        
        double eps = 1e-6, step = 100;
        double best = INT_MAX;
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        
        double x = 0, y = 0;
        
        while (step > eps) {
            bool moved = false;
            
            for (int i = 0; i < 4; ++i) {
                double nx = x + step * dx[i];
                double ny = y + step * dy[i];
                double newD = dist(nx, ny);
                if (newD < best) {
                    moved = true;
                    x = nx;
                    y = ny;
                    best = newD;
                    break;
                }
            }
            
            if (!moved) {
                step /= 2;
            }
        }
        
        return best;
    }
};