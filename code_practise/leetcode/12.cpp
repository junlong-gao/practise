class Solution {
public:
    string intToRoman(int num) {
        unordered_map<int, string> t{
            {1, "I"},
            {4, "IV"},
            {5, "V"},
            {9, "IX"},
            {10, "X"},
            {40, "XL"},
            {50, "L"},
            {90, "XC"},
            {100, "C"},
            {400, "CD"},
            {500, "D"},
            {900, "CM"},
            {1000, "M"}
        };
        string ret;
        while (num) {
            int m = 1;
            for (auto pr : t) {
                if (pr.first <= num) {
                    m = max(m, pr.first);
                }
            }
            
            ret += t[m];
            num -= m;
        }
        
        return ret;
    }
};
