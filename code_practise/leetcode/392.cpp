class Solution {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<int>> cMap(256);
	for (int i = 0; i < t.length(); ++i) {
		cMap[t[i]].push_back(i);
	}
	int cur = -1;
	for (int i = 0; i < s.length(); ++i) {

		auto it = upper_bound(cMap[s[i]].begin(), cMap[s[i]].end(), cur);
		if (it == cMap[s[i]].end()) return false;
		cur = *it;
	}

	return true;
    }
};



