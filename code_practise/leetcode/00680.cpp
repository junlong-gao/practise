class Solution {
public:
    bool validPalindrome(string s) {
        auto isPalindrome = [&] (int n, int m) {
            for (int i = n, j = m; i < j; ++i, --j) {
                if (s[i] != s[j]) return false;
            }
            
            return true;
        };
        for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
           if (s[i] == s[j]) continue; 
           else {
               return isPalindrome(i + 1, j) || isPalindrome(i, j - 1);
           }
        }
        
        return true;
    }
};
