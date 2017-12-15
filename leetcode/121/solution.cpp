class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int cur_min = 100000000;
        int cur_Delta = 0;
        for (int i = 0; i < (int) prices.size(); ++i){
            cur_min = min(cur_min, prices[i]);
            cur_Delta = max(cur_Delta, prices[i] - cur_min);
        }
        return cur_Delta;
    }
};
