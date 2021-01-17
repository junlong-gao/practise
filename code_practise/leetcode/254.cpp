class Solution {
    void search(int lastUsed, int n, vector<int> &sofar, vector<vector<int>> *output) {
        if (n == 1) {
            if (sofar.size() > 1) { // see below
                output->push_back(sofar);
            }
        }
        
        // 2 cases: full case (and elimitated if this is applied at the original problem)
        if (lastUsed <= n) {
            sofar.push_back(n);
            search(n, 1, sofar, output);
            sofar.pop_back();
        }
        
        for (int i = lastUsed; i <= n / i; i++) {
            if (n % i == 0) {
                sofar.push_back(i);
                search(i, n / i, sofar, output);
                sofar.pop_back();
            }
        }
    }
public:
    vector<vector<int>> getFactors(int n) {
        vector<int> tmp;
        vector<vector<int>> ret;
        search(2, n, tmp, &ret);
        return ret;
    }
};