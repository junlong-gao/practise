class Solution {
public:
    string freqAlphabets(string S) {
        string ret;
        int i = S.size() - 1;
        while (i >= 0) {
            if (S[i] == '#') {
                ret.push_back('a' + stoi(S.substr(i - 2, 2)) - 1);
                i -= 3;
            } else {
                ret.push_back('a' + S[i] - '1');
                i--;
            }
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};