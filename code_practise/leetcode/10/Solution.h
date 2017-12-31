#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include<string>
#include<vector>

using namespace std;


class Solution {
public:
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(2, vector<bool>(p.length()+1, false));
        dp[0][0] = true;
        if(dp[0].size() > 1) dp[0][1] = false;
        for(int j = 2; j < dp[0].size(); ++j){
           dp[0][j] = dp[0][j - 2] && p[j - 1] == '*';
        }

        for(int i = 1; i < s.size()+1 ; ++i){
            dp[i%2][0] = false;
            dp[i%2][1] = (p[0] == '*')?false:((p[0] == '.' || p[0] == s[i-1])&&dp[(i+1)%2][0]);
            for(int j = 2; j < dp[0].size(); ++j){
                if(p[j - 1] == '*'){
                    dp[i%2][j] = (dp[(i+1)%2][j]&&(p[j-2] == '.' || p[j-2]==s[i-1]))|| dp[i%2][j-2];
                }else{
                    dp[i%2][j] = dp[(i+1)%2][j-1] && (p[j - 1] == '.' || p[j-1] == s[i-1]);
                }
            }
        }
        return dp[s.length()%2][p.length()];
    }
};


#endif //PRACTISE_SOLUTION_H
