class Solution {
public:
    string reverseWords(string s) {
        int i = 0;
        vector<string> ss;
        while (i < s.size() && s[i] == ' ') {i++;}
        while (i < s.size()) {
            int j = i;
            while (j < s.size() && s[j] != ' ') {j++;}
            if (j - i > 0) {
                for (int k = i, l = j - 1; k < l; k++, l--) {
                    swap(s[k], s[l]);
                }
                ss.push_back(s.substr(i, j - i));
            }
            i = j + 1;
        }
        
        string ret;
        while (ss.size()) {
            for (int i = 0, j = ss.back().size() - 1; i < j; i++, j--) {
                swap(ss.back()[i], ss.back()[j]);
            }
            ret += ss.back(); ss.pop_back();
            if (ss.size()) {
                ret += " ";
            }
        }        
        return ret;
    }
};