class Solution {
    struct ent_t {
      int s, e, p;  
    };
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<int> dp(profit.size());
        vector<ent_t> data;
        auto cmp = [](const ent_t &l, const ent_t &r) {
            if (l.e != r.e) {
                return l.e < r.e;
            }
            if (l.s != r.s) {
                return l.s < r.s;
            }
            return l.p < r.p;
        };
        
        for (int i = 0; i < profit.size(); ++i) {
            data.push_back(ent_t{startTime[i], endTime[i], profit[i]});
        }
        sort(data.begin(), data.end(), cmp);
        
        for (int i = 0; i < profit.size(); ++i) {
            if (i == 0) {
                dp[i] = data[i].p;
            } else {
                ent_t fake = data[i];
                fake.e = fake.s;

                auto it = upper_bound(data.begin(), data.begin() + i, fake, cmp);
                if (it == data.end() || it == data.begin()) {
                    dp[i] = data[i].p;
                } else {
                    dp[i] = data[i].p + dp[(it - data.begin() - 1)];
                }
                dp[i] = max(dp[i], dp[i-1]);
            }
        }
        return dp.back();
    }
};