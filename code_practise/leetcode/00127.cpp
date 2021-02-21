class Solution {
    struct ent_t {
        string n;
        int d;
    };
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> nodes;
        for (auto &w : wordList) {
            nodes.insert(w);
        }
        if (nodes.count(endWord) == 0) {
            return 0;
        }
        deque<ent_t> q{ent_t{beginWord, 0}};
        nodes.erase(beginWord);
        while (q.size()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                auto top = q.front(); q.pop_front();
                if (top.n == endWord) {
                    return top.d + 1;
                }
                for (int j = 0; j < top.n.size(); ++j) {
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (top.n[j] == c) {
                            continue;
                        }
                        char t = top.n[j];
                        top.n[j] = c;
                        if (nodes.count(top.n) == 0) {
                            top.n[j] = t;
                            continue;
                        }
                        nodes.erase(top.n);
                        q.push_back(ent_t{top.n, top.d + 1});
                        top.n[j] = t;
                    }
                }
            }
        }
        return 0;
    }
};