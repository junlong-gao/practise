class Solution {
public:
    string addBinary(string a, string b) {
        string ret;
        int c = 0;
        int i = a.size() - 1, j = b.size() - 1;
        for (; i >= 0 && j >= 0; --i, --j) {
            int v = ((a[i] - '0') + (b[j] - '0') + c);
            ret.push_back(v % 2 + '0');
            c = v / 2;
        }
        
        for (; i >= 0; --i) {
            int v = (a[i] - '0' + c);
            ret.push_back(v % 2 + '0');
            c = v / 2;
        }
        for (; j >= 0; --j) {
            int v = (b[j] - '0' + c);
            ret.push_back(v % 2 + '0');
            c = v / 2;
        }
        
        if (c) {
            ret.push_back(c + '0');
        }
        reverse(ret.begin(), ret.end());
        
        return ret;
    }
};
