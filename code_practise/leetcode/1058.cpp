class Solution {
/*
dp[i][v] = min cost of archiving v with first i elements.

dp[0][v] = 0 if v
           infty else
           
dp[i][0] = dp[i - 1][0] + p[i - 1]          
dp[i][v] = min(1 - p[i - 1] + dp[i - 1][v - 1], p[i - 1] + dp[i - 1][v])
           
*/
public:
    string minimizeError(vector<string>& prices, int target) {
        vector<double> p;
        for (int i = 0; i < prices.size(); ++i) {
            double v = stod(prices[i]);
            target -= static_cast<int>(floor(v));
            double d = v - floor(v);
            if (abs(d) >= numeric_limits<double>::epsilon()) {
                p.push_back(d);
            }
        }
        
        if (target < 0) {
            return "-1";
        }
        vector<vector<double>> dp(p.size() + 1, vector<double>(target + 1));
        int inf = INT_MAX / 2 - 1;
        for (int i = 0; i <= p.size(); ++i) {
            for (int v = 0; v <= target; ++v) {
                if (i == 0) {
                   if (v == 0) {
                       dp[i][v] = 0;
                   } else {
                       dp[i][v] = inf;
                   }
                } else if(v == 0) {
                    dp[i][v] = inf;
                    if (dp[i - 1][v] != inf) {
                        dp[i][v] = dp[i-1][v] + p[i-1];
                    }
                }else {
                    dp[i][v] = inf;
                    if (dp[i-1][v-1] != inf) {
                        dp[i][v] = min(dp[i][v], 1 - p[i - 1] + dp[i-1][v-1]);
                    }
                    if (dp[i-1][v] != inf) {
                        dp[i][v] = min(dp[i][v], p[i-1]+dp[i-1][v]);
                    }
                }
            }
        }
        
        if (dp[p.size()][target] != inf) {
            std::ostringstream os;
            os << std::fixed << std::setprecision(3) << dp[p.size()][target];
            return os.str();
        }
        
        return "-1";
    }
};