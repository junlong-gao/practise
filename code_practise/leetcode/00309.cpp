class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int sold = 0, coolDown = 0, holding = -prices[0];
        for (int i = 1; i < prices.size(); ++i) {
            int newHolding = max(
                coolDown - prices[i],
                holding
            );
            
            int newSold = max(
                holding + prices[i],
                max(sold, coolDown)
            );
            
            int newCoolDown = max(
                sold,
                coolDown
            );
            sold = newSold;
            coolDown = newCoolDown;
            holding = newHolding;
        }
        return max(sold, coolDown);
    }
};