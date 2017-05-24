class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<2) return 0;
        int total = 0;
        for(int i = 0; i < prices.size()-1; i++){
            if(prices[i+1]>prices[i])
                total += prices[i+1]-prices[i];
        }
        return total;
    }
};
