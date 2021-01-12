class Solution {
    vector<vector<int>> dp;
    int search(int ii, int dd, vector<int> &jd) {
        if (dp[ii][dd] != INT_MAX) {
            return dp[ii][dd];
        }
        int &ret = dp[ii][dd];
        
        if (dd == 0) {
            assert(ii == jd.size());
            return ret = 0;
        }
        if (dd == 1) {
            int curMax = jd[ii];
            for (int i = ii; i < jd.size(); ++i) {
                curMax = max(jd[i], curMax);
            }
            return ret = curMax;
        }
        
        int curMax = jd[ii];
        for (int k = ii; k + 1 + dd - 1 <= jd.size(); k++) {
            curMax = max(curMax, jd[k]);
            ret = min(ret, curMax + search(k + 1, dd - 1, jd));
            assert(ret != -1);
        }
        return ret;
    }
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        if (jobDifficulty.size() < d) {
            return -1;
        }
        dp.resize(jobDifficulty.size() + 1, vector<int>(d + 1, INT_MAX));
        return search(0, d, jobDifficulty);
    }
};
