class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<int>> mp;
        for (int i = 0; i < strs.size(); ++i) {
            auto s = strs[i];
            sort(s.begin(), s.end());
            mp[s].push_back(i);
        }
        
        vector<vector<string>> ret;
        for (auto &pr : mp) {
            ret.push_back({});
            for (int i : pr.second) {
                ret.back().push_back(strs[i]);
            }
        }
        
        return ret;
    }
};
