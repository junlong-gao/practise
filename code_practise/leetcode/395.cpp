class Solution {
public:
    int longestSubstring(string s, int k) {
        int ret = 0;
        for (int c = 1; c <= 26; ++c) {
            unordered_map<char, int> refcount;
            int j = 0, i = 0;
            // refcount track char occurance in substr [i, j)

            while (j < s.size()) {
                // expand
                while (refcount.size() <= c && j < s.size()) {
                    refcount[s[j]]++;
                    j++;

                    // check [i, j)
                    if (refcount.size() == c &&
                        std::all_of(refcount.begin(), refcount.end(),
                        [&k](const auto& pr){ return pr.second >= k; })) {
                        ret = max(ret, j - i);
                    }
                }

                // shrink
                while (refcount.size() > c && i < j) {
                    refcount[s[i]]--;
                    if (refcount[s[i]] == 0) {
                        refcount.erase(s[i]);
                    }
                    i++;
                }
            }
        }

        return ret;
    }
};