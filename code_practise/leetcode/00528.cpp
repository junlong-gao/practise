class Solution {
    template <typename T>
    using v = vector<T>;
    
    v<int> p;
public:
    Solution(vector<int>& w) {
        for (int i = 0; i < w.size(); ++i) {
            if (p.empty()) {
                p.push_back(w[i]);
            } else {
                p.push_back(p.back() + w[i]);
            }
        }
    }
    
    int pickIndex() {
        int k = rand() % p.back();
        
        int lo = -1; int hi = p.size() - 1;
        while (hi - lo > 1) {
            int m = lo + (hi - lo) / 2;
            if (p[m] > k) {
                hi = m;
            } else {
                lo = m;
            }
        }
        
        return hi;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
