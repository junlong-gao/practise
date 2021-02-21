class Solution {
public:
    string multiply(string num1, string num2) {
        vector<int> ret(num1.size() + num2.size(), 0);
        for (int i = num1.size() - 1; i>=0; --i) {
            int carry = 0;
            int d1 = num1[i] - '0';
            int ii = num1.size() - 1 - i;
            for (int j = num2.size() - 1; j >= 0; --j) {
                int d2 = num2[j] - '0';
                int jj = num2.size() - 1 - j;
                ret[ii + jj] += d1 * d2 + carry;
                carry = ret[ii + jj] / 10;
                ret[ii + jj] %= 10;
                //cout << ii << " " << jj << " " << ret[ii + jj] << endl;
            }
            ret[ii + num2.size()] += carry;
        }
        
        int i = ret.size() - 1;
        while (i >= 0 && ret[i] == 0) {
            --i;
        }
        string s;
        for (int j = i; j >= 0; --j) {
            s.push_back(ret[j] + '0');
        }
        return s.empty() ? "0" : s;
    }
};
