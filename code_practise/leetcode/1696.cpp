class Solution {
    /*
    dp[i] = max score to arrive at index i
    dp[0] = nums[0]
    dp[i] = max_{i - k <= j <= i}(dp[j]) + nums[i];
    */
    struct ent_t {
        int v; int idx;
    };
public:
    int maxResult(vector<int>& nums, int k) {
        vector<int> dp(nums.size());
        list<ent_t> cands;
        auto cmp = [](const list<ent_t>::iterator &l, const list<ent_t>::iterator &r) {
            if (l->v != r->v) {
                return l->v < r->v;
            }
            return l->idx < r->idx;
        };
        set<list<ent_t>::iterator, decltype(cmp)> pq(cmp);
        for (int i = 0; i < nums.size(); ++i) {
            if (i == 0) {
                dp[i] = nums[i];
            } else {
                dp[i] = (*pq.rbegin())->v + nums[i];
                if (cands.size() == k) {
                    pq.erase(cands.begin());
                    cands.pop_front();
                }
            }
            cands.push_back(ent_t{dp[i], i});
            pq.insert(prev(cands.end()));
        }
        
        return dp.back();
    }
};