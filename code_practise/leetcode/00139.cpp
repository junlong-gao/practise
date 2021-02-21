/* trie + memorization */
class Solution {
    vector<int> dp;
    struct TrieLink {
        unordered_map<char, TrieLink*> children;
        bool isWord;
        ~TrieLink() {
            for (auto c : children) {
                delete c.second;
            }
        }
        void add(const string &s, int i) {
            if (i == s.size()) {
                isWord = true;
            } else {
                if (children.count(s[i]) == 0) {
                    children[s[i]] = new TrieLink;
                    children[s[i]]->isWord = false;
                }
                children[s[i]]->add(s, i + 1);
            }
        }
    };
    TrieLink root;
    bool search(string &s, int i) {
        if (i == s.size()) {
            return true;
        }
        if (dp[i] != -1) {
            return dp[i];
        }
        TrieLink *r = &root;
        for (int j = i; j < s.size(); ++j) {
            if (r->children.count(s[j]) == 0) {
                break;
            }
            r = r->children[s[j]];
            if (r->isWord) {
                if (search(s, j + 1)) {
                    dp[i] = 1;
                    return true;
                }
            }
        }
        dp[i] = 0;
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        for (const auto & w : wordDict) {
            root.add(w, 0);
        }
        dp.resize(s.size(), -1);
        return search(s, 0);
    }
};
