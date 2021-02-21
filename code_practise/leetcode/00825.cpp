class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        sort(ages.begin(), ages.end());
        int ret = 0;
        for (int i = 0; i < ages.size(); ++i) {
            int lo = ages[i] / 2 + 7;
            int hi = ages[i];
            auto loit = upper_bound(ages.begin(), ages.end(), lo);
            auto hiit = upper_bound(ages.begin(), ages.end(), hi);
            if (loit < hiit) {
               ret += hiit - loit;
            }
            if (loit < hiit && loit <= ages.begin() + i && hiit > ages.begin() + i) {
                ret--;
            }
        }
        return ret;
    }
};
