class Solution {
    vector<string> words;
    struct trie {
        unordered_map<char, trie*> children;
        int counter = 0;
        int idx;
        void add_helper(const string & s, int sofar, int ii) {
            if (sofar == s.size()) {
                idx = ii;
                return;
            }

            counter++;
            char c = s[sofar];
            if (children.count(c) == 0) {
                children[c] = new trie;
            }
            children[c]->add_helper(s, sofar + 1, ii);
        }
        void add(const string & s, int ii) {
            add_helper(s, 0, ii);
        }

        void search_helper(int d, const string & prefix, vector<string>& dump, vector<string> & words) {
            assert(d == prefix.size());
            if (counter == 1) {
                trie *node = this;
                int counter = 0;
                while (!node->children.empty()) {
                    node = node->children.begin()->second;
                }

                int idx = node->idx;
                const string & ret = words[idx];
                string t = prefix + to_string(ret.size() - prefix.size() - 1) + ret.back();
                dump[idx] = t.length() < ret.length() ? t : ret;
            } else {
                for (auto cc : children) {
                    cc.second->search_helper(d + 1, prefix + cc.first, dump, words);
                }
            }
        }

        void search(vector<string>& dump, vector<string> & words) {
            for (auto cc : children) {
                string t = "";
                t += cc.first;
                cc.second->search_helper(1, t, dump, words);
            }
        }

        ~trie() {
            for (auto cc: children) {
                delete cc.second;
            }
        }
    };
public:
    vector<string> wordsAbbreviation(vector<string>& dict) {
        int n = dict.size();
        std::swap(dict, words);
        vector<string> dump(n);

        unordered_map<int, unordered_map<string, vector<int>>> buckets;
        for (int i = 0; i < words.size(); ++i) {
            const string &s = words[i];
            string t = "";
            t += s.front();
            t += s.back();
            buckets[s.length()][t].push_back(i);
        }

        for (const auto & b : buckets) {
            for (const auto & group_pr : b.second) {
                const auto & group = group_pr.second;
                trie root;
                for (const auto & idx : group) {
                    root.add(words[idx], idx);
                }
                root.search(dump, words);
            }
        }

        return dump;
    }
};

/*
Tests:
["me","god","like","face",  "internal",  "internet", "interval", "intension", "intrusion"]
["internal", "interrval"]
*/