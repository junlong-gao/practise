class Solution {
    bool check(const vector<double> &intervals, double D, int K) {
        for (int i = 0; i < intervals.size(); ++i) {
            int need = std::ceil(intervals[i] / D) - 1;
            if (K < need) {
                return false;
            }
            K -= need;
        }
        return true;
    }
public:
    double minmaxGasDist(vector<int>& stations, int K) {
        vector<double> intervals;
        double lo = 0, hi = 0, eps = 0.000000001;
        for (int i = 1; i < stations.size(); ++i) {
            intervals.push_back(stations[i] - stations[i - 1]);
            hi = std::max(hi, intervals.back());
        }
        
        while (hi - lo > eps) {
            double mid = lo + (hi - lo) / 2;
            if (check(intervals, mid, K)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        
        return lo;
    }
};
