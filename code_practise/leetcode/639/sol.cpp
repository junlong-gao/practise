class Solution {
    using ll = long long;
    const ll M = 1000000000+7;
public:
    int numDecodings(string s) {
        if(s.length() == 0) return 1;
        if(s.length() == 1) return ((s[0] == '*')? 9 : (s[0] == '0'? 0 : 1));
        vector<ll> dp(s.length() + 1);
        dp[0] = 1;
        dp[1] = ((s[0] == '*')? 9 : (s[0] == '0'? 0 : 1));
        for(size_t i = 2; i <= s.length(); ++i){
            char prev = s[i - 2], cur = s[i-1];
            dp[i] = 0;
            auto add_func = [&](ll b){
                dp[i] = (dp[i] + b%M) %M;
            };
            if(prev == '0'){
                add_func(single(i, s, dp));
            } else if (prev == '1'){
                add_func(single(i, s, dp));
               
                add_func(f1cur(i, s, dp));
            } else if (prev == '2'){
                add_func(single(i, s, dp));
                //cout << dp[i] << endl;
                add_func(f2cur(i, s, dp));
                //cout << dp[i] << endl;
                //cout << "s" << endl;
            } else if (prev == '*'){
                add_func(single(i, s, dp));
                add_func(f1cur(i, s, dp));
                add_func(f2cur(i, s, dp));
            } else {
                add_func(single(i, s, dp));
            }
            //cout << dp[i] << endl;
        }
        return dp.back()%M;
    }
    int single(size_t idx, string& s, vector<ll>& dp){
        if(s[idx - 1] == '0'){ // cur is 0
            if(s[idx - 2] == 1 || s[idx-2] == 2){
                return dp[idx - 2];
            }else{
                return 0;
            }
        }
        //cur is *
        if(s[idx - 1] == '*') return (dp[idx - 1]*9) % M;
        return dp[idx - 1];
    }
    
    int f1cur(size_t idx, string& s, vector<ll>& dp){
        if(s[idx - 1] == '*') return (dp[idx - 2] * 9) % M;
        return dp[idx - 2];
    }
    
    int f2cur(size_t idx, string& s, vector<ll>& dp){
        if(s[idx - 1] == '*') return (dp[idx - 2] * 6) % M;
        if(s[idx - 1] >= '7') return 0;
        return dp[idx - 2];
    }
    
};