class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        if (m * k > bloomDay.size()) return -1;
        auto check = [&bloomDay, &k, &m] (int time) {
            int count = 0;
            int i = 0;
            while (i < bloomDay.size()) {
                while (i < bloomDay.size() && bloomDay[i] > time) { i++; }
                int j = i;
                while (j < bloomDay.size() && bloomDay[j] <= time) {
                    j++;
                    if (j - i == k) {
                        count++;
                        break;
                    }
                }
                i = j;
            }
            return count >= m;
        };
        int lo = 0, hi = 1e9;
        while (hi - lo > 1) {
            int mid = lo + (hi - lo) / 2;
            if (check(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }

        return hi;
    }
};