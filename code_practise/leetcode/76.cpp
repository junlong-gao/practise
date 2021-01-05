auto f = [](){
    ios::sync_with_stdio(false);cin.tie(NULL);return 0;
}();

class Solution {
#define Vec vector
public:
    string minWindow(string s, string t) {
        Vec<int> p(256, 0); Vec<int> q(256, 0);
        int toFind = 0;
        for (int i = 0; i < t.size(); ++i) {
            if (q[t[i]] == 0) {
                toFind++;
            }
            q[t[i]]++;
        }
        
        int i = 0; int j = 0; int best = INT_MAX;
        int reti, retj;
        int found = 0;
        while (j < s.size()) {
            while (j < s.size() && found < toFind) {
                p[s[j]]++;
                j++;
                if (p[s[j-1]] == q[s[j-1]]) {
                    found++;
                }
            }
            while (i < j && found == toFind) {
                if (j - i < best) {
                    best = j - i;
                    reti= i;
                    retj = j;
                }
                p[s[i]]--;
                i++;
                if (p[s[i-1]] < q[s[i-1]]) {
                    found--;
                }
            }
        }
        if (best == INT_MAX) {
            return "";
        }
        return s.substr(reti, retj - reti);
    }
};
