class Solution {
    int w;
    int ceiling(int n, int d) {
        int q = n / d;
        if (q * d < n) q++;
        return q;
    }
    string line_justifier(int& it, int& ed, vector<string>& words) {
        int spaceleft = w;
        assert(it != ed);
        vector<int> bag;
        string ret;
        bag.push_back(it);
        ret += words[bag[0]];
        spaceleft -= words[it].length();
        assert(spaceleft >= 0);
        ++it;
        
        while(true) {
            if (it == ed) {
                //this is the last line
                for (int i = 1; i < bag.size(); ++i) {
                    ret += ' ';
                    ret += words[bag[i]];
                }
                return ret + string(w - ret.length(), ' ');
            }
            if (words[it].length() + 1 > spaceleft) {
                //justify
                int slot = bag.size() - 1;
                if (slot == 0) return ret + string(w - ret.length(), ' ');
                
                int gap = ceiling(spaceleft, slot);
                int exceeding = slot * gap - spaceleft;
                string shortgap(gap, ' '), longgap(gap + 1, ' ');
                for (int i = 0; i < slot - exceeding; ++i) {
                    ret += longgap;
                    ret += words[bag[i + 1]];
                }
                for (int i = slot - exceeding; i < slot; ++i) {
                    ret += shortgap;
                    ret += words[bag[i + 1]];
                }
                assert(ret.length() == w);
                return ret;
            }
            bag.push_back(it);
            spaceleft -= words[it].length() + 1;
            ++it;
        }
    }
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ret;
        w = maxWidth;
        int it = 0;
        int ed = words.size();
        while (it != ed) {
            ret.emplace_back(line_justifier(it, ed, words));
        }
        return ret;
    }
};
