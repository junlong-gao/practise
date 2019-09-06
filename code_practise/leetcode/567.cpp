class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.size() > s2.size()) return false;
        vector<int> refcount(26, 0), sofar(26, 0);
        for (int i = 0; i < s1.size(); ++i) {
            refcount[s1[i] - 'a']++;
            sofar[s2[i] - 'a']++;
        }
        
        if (refcount == sofar) return true;
        for (int j = 1; j + s1.size() <= s2.size(); ++j) {
            sofar[s2[j - 1] - 'a']--;
            sofar[s2[j + s1.size() - 1] - 'a']++;
            if (refcount == sofar) return true;
        }
        
        return false;
    }
};
