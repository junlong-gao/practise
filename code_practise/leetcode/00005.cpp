class Solution {
public:
    string longestPalindrome(string s) {
        int ret = 1;
        int lb = 0, rb = 0;
        for (int i = 0; i < s.size(); ++i) {
           int l = i; int r = i;
           while (r + 1 < s.size() && s[r+1] == s[r]) {
              r++;
           }

           while (l - 1 >= 0 && r + 1 < s.size() && s[l-1] == s[r+1] ) {
              l--; r++;
           }

         if (r - l + 1 > ret) {
            ret = r - l + 1;
            lb = l; rb = r;
         }
        }
        return s.substr(lb, rb - lb + 1);
    }
};
