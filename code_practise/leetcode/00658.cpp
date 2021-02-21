class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> ret;
        int n = arr.size(), lo = 0, hi = n;
        assert(k > 0 && k <= n);
        while (hi - lo > 1) {
            int mid = lo + (hi - lo) / 2;
            int val = arr[mid];
            if (val >= x) {
                hi = mid;
            } else {
                lo = mid;
            } 
        }
        while (k && hi < arr.size() && lo >= 0) {
            if (abs(arr[hi] - x) < abs(arr[lo] - x)) {
                ret.push_back(arr[hi++]);
            } else {
                ret.push_back(arr[lo--]);
            }
            k--;
        }
        while (k && hi < arr.size()) {
            ret.push_back(arr[hi++]);
            k--;
        }
        while (k && lo >= 0) {
            ret.push_back(arr[lo--]);
            k--;
        }
        sort(ret.begin(), ret.end());
        return ret;
    }
};


