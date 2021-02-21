class Solution {
public:
    string frequencySort(string s) {
        vector<pair<char, int>> alpha(256);
        for (int i = 0; i < 256; ++i) {
            alpha[i].first = i;
            alpha[i].second = 0;
        }
        for (char c : s) {
            alpha[c] = pair<char, int>{alpha[c].first, alpha[c].second + 1};
        }
        sort(alpha.begin(), alpha.end(), [&](const pair<char, int> l,
                                             const pair<char, int> r){
           return l.second > r.second; 
        });
        string ret;
        for (int i = 0; i < 256; ++i) {
            for (int j = 0; j < alpha[i].second; ++j) {
                ret += alpha[i].first;
            }
        }
        return ret;
    }
};
