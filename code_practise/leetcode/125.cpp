class Solution {
public:
    bool isPalindrome(string s) {
        string t;
        for (auto c : s) {
            if (isalpha(c) || isdigit(c)) {
                t.push_back(c);
            }
        }
        swap(t, s);
        for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
           if (tolower(s[i]) == tolower(s[j])) continue; 
           else return false;
        }
        
        return true;
    }
};
