class Solution {
    unordered_map<int, string> digits {
        {1, "One"},
        {2, "Two"},
        {3, "Three"},
        {4, "Four"},
        {5, "Five"},
        {6, "Six"},
        {7, "Seven"},
        {8, "Eight"},
        {9, "Nine"},
    }, twenties {
        {10, "Ten"},
        {11, "Eleven"},
        {12, "Twelve"},
        {13, "Thirteen"},
        {14, "Fourteen"},
        {15, "Fifteen"},
        {16, "Sixteen"},
        {17, "Seventeen"},
        {18, "Eighteen"},
        {19, "Nineteen"},
    }, tens {
        {2, "Twenty"},
        {3, "Thirty"},
        {4, "Forty"},
        {5, "Fifty"},
        {6, "Sixty"},
        {7, "Seventy"},
        {8, "Eighty"},
        {9, "Ninety"},
    };
    string printer(int n) {
        //cout << n << endl;
        assert(n > 0 && n < 1e3);
        int h = n / 100;
        string ret;
        if (h > 0) {
            ret += digits.at(h) + " Hundred ";
        }
        n %= 100;
        
        if (n >= 20) {
            ret += tens.at(n / 10) + " ";
            n %= 10;
        }
        
        if (n > 0 && n < 10) {
            ret += digits.at(n) + " ";
        } else if (n >= 10) {
            ret += twenties.at(n) + " ";
        }
        return ret;
    }
    
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        string ret;
        for (auto delimiter : vector<pair<string, int>>{
            {"Billion ", 1e9},
            {"Million ", 1e6},
            {"Thousand ", 1e3},
            {"", 1}
        }) {
            const string &unit =  delimiter.first;
            int d = delimiter.second;
            if (num / d > 0) {
                ret += printer(num / d) + unit;
                num %= d;
            }
        }
        
        if(ret.back() == ' ') {
            ret.pop_back();
        }
        return ret;
    }
};
