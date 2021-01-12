class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        unordered_map<string, vector<string>> lk;
        for (int i = 0; i < strs.size(); ++i) {
            string t = strs[i];
            sort(t.begin(), t.end());
            lk[t].emplace_back(strs[i]);
        }
        vector<vector<string>> ret;
        for (auto &pr : lk) {
            ret.emplace_back(std::move(pr.second));
        }
        return ret;
    }
};