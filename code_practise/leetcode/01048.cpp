class Solution {
/* longest path in DAG
dp[i] = max {dp[j] + 1 | word[i] is a predecessor of word[j]}
max of empty set is 0
*/
    vector<int> dp;
    int search(vector<string>& words, int i) {
        if (dp[i] != -1) return dp[i];
        int &ret = dp[i];
        ret = 1;
        for (int j = 0; j < words.size(); ++j) {
            if (words[i].size() != words[j].size() + 1) {
                continue;
            }
            for (int k = 0; k < words[i].size(); ++k) {
                string t = words[i];
                t.erase(k, 1);
                if (t == words[j]) {
                    //cout << words[i] << "->" << words[j] << endl;
                    ret = max(ret, search(words, j) + 1);
                }
            } 
        }
        return ret;
    }
public:
    int longestStrChain(vector<string>& words) {
        dp.resize(words.size(), -1);
        int ret = 0;
        for (int i = 0; i < words.size(); ++i) {
            ret = max(ret, search(words, i));
        }
        return ret;
        
    }
};
