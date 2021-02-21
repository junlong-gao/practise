class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ret;
        vector<int> pref(26, 0), qref(26, 0);
        for (auto c : p){
            pref[c - 'a']++;
        }
        
        for (int i = 0, j = p.size();
             j <= s.size();
             ++i, ++j) {
            if (i == 0) {
                for (int k = 0; k < j; ++k) {
                    qref[s[k] - 'a']++;
                }
            } else {
                qref[s[i - 1] - 'a']--;
                qref[s[j - 1] - 'a']++;
            }
            
            if (pref == qref) {
                ret.push_back(i);
            }
        }
        
        return ret;
    }
};
