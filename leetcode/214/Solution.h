#ifndef SOLUTION_214
#define SOLUTION_214
#include <string>

namespace lee214{
    using namespace std;
    class Solution {
    public:
        int kmp(string&& s){
            vector<int> p(s.length(), 0);
            int k = 0;
            for(int i = 1; i < s.length(); ++i){
                while(k > 0 && s[k] != s[i]) k = p[k-1];
                if(s[k] == s[i]) k++;
                p[i] = k;
            }
            return p[s.length() -1];
            
        }
        string shortestPalindrome(string s) {
            string tmp = s;
            reverse(tmp.begin(), tmp.end());
            int num = kmp(s + "#" + tmp);
            return tmp.substr(0, s.length() - num) + s;
        }
    };
}

#endif