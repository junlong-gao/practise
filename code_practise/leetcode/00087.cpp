#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
class Solution {
    vector<vector<vector<int>>> dp;
    int n;
    bool search(string& s1, string& s2, int i, int j, int l){
        if(dp[i][j][l] < 0){
            int& ans = dp[i][j][l];
            if(l == 1){
                ans = s1[i] == s2[j] ? 1:0;
                return s1[i] == s2[j];
            }else{
                for(int k = i + 1; k < i + l; ++k){
                    if(search(s1, s2, i, j + l - (k-i), k - i)
                            &&search(s1, s2, k, j, l-(k-i))){
                        ans = 1; return 1;
                    }
                    if(search(s1, s2, i, j, k-i)
                            && search(s1,s2,k,j+(k-i),l-(k-i))){
                        ans = 1; return 1;
                    }
                }
                ans = 0; return 0;
            }
        }else{
            return dp[i][j][l] == 1;
        }
    }
public:
    bool isScramble(string s1, string s2) {
        n = s1.length(); 
        dp.resize(n);
        for(auto & ele : dp){
            ele.resize(n);
            for(auto& eles : ele){
                eles.resize(n + 1 , -1);
            }
        }
        return search(s1,s2,0,0,n);
    }
};

int main(){
    Solution s;
    string s1 = "great";
    string s2 = "rgtea";
    bool ok = s.isScramble(s1,s2);
    cout << (ok? "YES" : "NO")<< endl;

    return 0;
}
