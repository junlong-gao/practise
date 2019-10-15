class Solution {
    using ll = unsigned long long;
    const ll bi = 26;
    const ll M = 1e14 + 7;
    int check(string& S, int length) {
        unordered_map<ll, int> m;
        ll h = 0;
        ll b = 1;
        for (int i = 0; i < length; ++i) {
            h = ((h * bi) % M + S[i]) % M;
            b = (b * bi) % M;
        }
        m[h] = length - 1;
        for (int i = length; i < S.size(); ++i) {
            h = ((bi * h % M - (S[i - length] * b) % M + M) % M + S[i]) % M;            
            if (m.count(h)) {
                if (S.substr(i - length + 1, length) == S.substr(m[h] - length + 1, length)) {
                    return i;
                }
            } else {
                m[h] = i;       
            }
        }
        return -1;
    }
    
public:
    string longestDupSubstring(string S) {
        int l = 0, r = S.length();
        int best = 0; string retStr;
        while (l < r - 1) {
            int mid = (l + r) / 2;
            int ret = check(S, mid);
            if (ret > 0 && mid > best) {
                best = mid; retStr = S.substr(ret - mid + 1, mid);
            }
            
            if (ret > 0) {
                l = mid;
            } else {
                r = mid;
            }
        }
        
        return retStr;
    }
};
