class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> count;
        for (char c : s) {
            count[c]++;
        }
        int ans = 0;
        int best = 0; char c;
        for (auto pr : count) {
            if (pr.second % 2) {
                if (best < pr.second) {
                   best = max(best, pr.second);
                    c = pr.first; 
                }
            }
        }
        
        if (best) {
            count.erase(c);
            ans += best;
        }
        
        for (auto pr : count) {
            ans += (pr.second) / 2 * 2;
        }
        return ans;    
    }
};
