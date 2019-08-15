class Solution {
public:
    int nextGreaterElement(int n) {
        using ll = long long;
        vector<int> d;
        while (n) {
            d.push_back(n % 10);
            n /= 10;
        }
        
        int i = 1;
        while (i < d.size() && d[i] >= d[i - 1]) {
            i++;
        }
        if (i == d.size()) return -1;
        int j = 0;
        while (j < i && d[j] <= d[i]) {
            j++;
        }
        assert(j < i);
        swap(d[i],d[j]);
        for (int k = 0; k < i - k - 1; ++k) {
            swap(d[k], d[i - k - 1]);
        }
        ll ret = 0;
        for (int i = d.size() - 1; i >= 0; --i) {
            ret *= (ll)10;
            ret += (ll)d[i];
        }
        return ret > numeric_limits<int>::max() ? -1 : ret;
    }
};
