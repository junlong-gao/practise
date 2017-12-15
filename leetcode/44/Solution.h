#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(2, vector<bool>(p.length() + 1));

        dp[0][0] = true;
        for(int j = 1; j < p.length() + 1; ++j){
            dp[0][j] = (p[j - 1] == '*') && dp[0][j-1];
        }

        for(int i = 1; i < s.length() + 1; ++i){
            dp[i%2][0] = false;
            for(int j = 1; j < p.length() + 1; ++j){
               if(p[j - 1] != '*'){
                   dp[i%2][j] = ((s[i-1]==p[j-1]) || (p[j-1]=='?')) && dp[(i+1)%2][j-1];
               } else{
                   dp[i%2][j] = dp[(i+1)%2][j] || dp[i%2][j-1];
               }
            }
        }
        return dp[s.length() %2][p.length()];
    }
};