/* naive:
class Solution {
    vector<int> dp;
    int search(int i, const vector<vector<int>>& env) {
        if (dp[i] != -1) {
            return dp[i];
        }
        
        int &ret = dp[i];
        ret = 1;
        for (int j = 0; j < env.size(); ++j) {
            if (env[j][0] < env[i][0] && env[j][1] < env[i][1]) {
                ret = max(ret, search(j, env) + 1);
            }
        }
        
        return ret;
    }
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        dp.resize(envelopes.size(), -1);
        
        int ret = 0;
        for (int i = 0; i < envelopes.size(); ++i) {
            ret = max(ret, search(i, envelopes));
        }
        return ret;
    }
};
*/

/* sort by one dimension and find LIS for the other */
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envs) {
        sort(envs.begin(), envs.end(), [](const vector<int> &l, const vector<int> &r) {
            if (l[0] != r[0]) {
                return l[0] < r[0];
            }
            /*
            every solution gives an LIS, but every LIS does not give a solution.
            [1, 1] [1, 2] 
            has LIS 1, 2 but this does not give a solution.
            
            To avoid this, just make sure for the same width, height cannot form LIS:
            [1, 2] [1, 1]
            */
            return l[1] > r[1];
        });
        vector<int> dp;
        for (int i = 0; i < envs.size(); ++i) {
            auto it = lower_bound(dp.begin(), dp.end(), envs[i][1]);
            if (it == dp.end()) {
                dp.push_back(envs[i][1]);
            } else {
                *it = envs[i][1];
            }
        }
        return dp.size();
    }
};