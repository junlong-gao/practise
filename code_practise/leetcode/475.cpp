class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        using ll = long long;
        sort(houses.begin(), houses.end());
        if (houses.empty()) return 0;
        ll lo = 0, hi = houses.back() - houses.front() + 1;
        auto check = [&](int r) {
            int i = 0, curHeater = 0;
            // at houses i, curHeater is the first heater such that house i
            // falls outside the range of previous heater.
            while (i < houses.size() && curHeater < heaters.size()) {
                if (houses[i] < heaters[curHeater] - r) {return false;}
                while (i < houses.size() && houses[i] <= heaters[curHeater] + r) i++;
                curHeater++;
            }
            return i == houses.size();
        };
        
        while (hi - lo > 1) {
            ll mid = lo + (hi - lo) / 2;
            if (check(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        return hi;
    }
};
