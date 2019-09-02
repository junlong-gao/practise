class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        vector<int> o(26);
        for (int i = 0; i < order.size(); ++i) {
            o[order[i]-'a'] = i;
        }
        
        for (int i = 0; i + 1 < words.size(); ++i) {
            auto &w1 = words[i];
            auto &w2 = words[i + 1];
            int j = 0; int k = 0;
            while (j < w1.size() && k < w2.size() && w1[j] == w2[k]) {
                j++; k++;
            }
            if (j == w1.size()) {
                continue;
            }
            
            if (k == w2.size()) {
                return false;
            }
            
            if (o[w1[j] - 'a'] > o[w2[k] - 'a']) {
                return false;
            }
        }
        
        return true;
    }
};
