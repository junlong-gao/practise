class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int i = 0, j= 0;
        while (i < abbr.size() && j < word.size()) {
            if (isdigit(abbr[i]) && abbr[i] != '0') {
                int t = i;
                while(i < abbr.size() && isdigit(abbr[i])) {
                    i++;
                }
                j += stoi(abbr.substr(t, i - t));
            } else {
                if (word[j] != abbr[i]) return false;
                j++; i++;
            }
        }
        
        return i == abbr.size() && j == word.size();
    }
};
