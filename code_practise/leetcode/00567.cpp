class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> refcount(256, 0), tmp(256, 0);
        for (auto c : s1) {
            refcount[c]++;
        }
        
        int i = 0;
        while (i < s2.size()) {
            tmp[s2[i]]++;
            if (i + 1 >= s1.size()) {
                if (refcount == tmp) {
                    return true;
                }
                tmp[s2[i - s1.size() + 1]]--;
            }
            i++;
        }
        return false;
    }
};