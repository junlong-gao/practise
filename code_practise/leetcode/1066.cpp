class Solution {
    void setbit(int& v, int idx) {
        v |= (1 << idx);
    }
    void clearbit(int& v, int idx) {
        v &= ~(1 << idx);
    }
    bool checkbit(int v, int idx) {
        return (v >> idx) & 1;
    }
    
    vector<int> dp; // dp[v] is the opt of subproblem total \ v
    int compute(vector<vector<int>>& workers,
                vector<vector<int>>& bikes,
                int usedBikes,
                int workerIdx) {
        if (workerIdx == workers.size()) {
            return 0;
        }
        int &ret = dp[usedBikes];
        if (ret != INT_MAX) return ret;
        
        for (int i = 0; i < bikes.size(); ++i) {
            if (checkbit(usedBikes, i)) continue;
            setbit(usedBikes, i);
            int d = abs(workers[workerIdx][0] - bikes[i][0]) +
                    abs(workers[workerIdx][1] - bikes[i][1]);
            ret = min(ret, d + compute(workers, bikes, usedBikes, workerIdx + 1));
            clearbit(usedBikes, i);
        }
        
        assert(ret != INT_MAX);
        return ret;
    }
public:
    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        dp.resize((1 << bikes.size()), INT_MAX);
        return compute(workers, bikes, 0, 0);
    }
};
