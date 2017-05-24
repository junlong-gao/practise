//
// Created by junlong on 8/6/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H

#include<string>
#include<vector>

using namespace std;


class Solution {
public:
    int numDecodings(string s) {
        vector<int> dp(s.length() + 1);
        dp[0] = 1;
        if(s.length() == 0) return 0;
        dp[1] = (s[0]>='1' && s[0]<='9')? 1: 0;
        for(int i = 2; i < s.length() + 1; ++i){
            if(s[i - 2] == '1'){
               if(s[i-1] >= '1' && s[i-1] <= '9') {
                   dp[i] = dp[i-1] + dp[i-2];
               }else{
                   dp[i] = dp[i-2];
               }
            }else if (s[i-2] == '2'){
               if(s[i-1] >= '1' && s[i-1] <= '6'){
                   dp[i] = dp[i-1] + dp[i-2];
               }else if (s[i-1] >= '7' && s[i-1] <= '9'){
                   dp[i] = dp[i-1];
               }else{
                   dp[i] = dp[i-2];
               }
            }else{
                if(s[i-1] != '0'){
                    dp[i] = dp[i-1];
                }else{
                    dp[i] = 0;
                }
            }
        }
        return dp[s.length()];

    }
};


#endif //PRACTISE_SOLUTION_H
