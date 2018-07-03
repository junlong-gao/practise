class Solution {

    // trace back a path
    void ctor(vector<vector<string>> &ret,
              const unordered_map<string, vector<string>> &p,
              const string &target,
              vector<string> &curPath) {
        assert(curPath.size() > 0);

        if (curPath.back() == target) {
            reverse(curPath.begin(), curPath.end());
            ret.push_back(curPath);
            reverse(curPath.begin(), curPath.end());
            return;
        }

        for (const auto & next : p.at(curPath.back())) {
            curPath.push_back(next);
            ctor(ret, p, target, curPath);
            curPath.pop_back();
        }

        return;
    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        if (beginWord == endWord) return {{beginWord}};
        unordered_set<string> bag(wordList.begin(), wordList.end());
        if (bag.count(endWord) == 0) return {};

        unordered_map<string, vector<string>> p;
        unordered_set<string> q;
        q.insert(beginWord);
        bag.erase(beginWord);
        while (q.size() > 0) {
            unordered_set<string> next;
            for (string w : q) {
                string pw = w;
                for (int i = 0; i < w.size(); ++i) {
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (w[i] == c) continue;
                        swap(w[i], c);

                        if (bag.count(w) == 1) {
                            bag.erase(w);
                            p[w].push_back(pw);
                            next.insert(w);
                        } else if (next.count(w) == 1) { // multiparent only happens inter-frontier.
                            p[w].push_back(pw);
                        }

                        swap(w[i], c);
                    }
                }
            }

            swap(q, next);
            // we must defer to here to make sure we have collected all endWord's parents
            if (q.count(endWord) == 1) {
                vector<string> tmp {endWord};
                vector<vector<string>> ret;
                ctor(ret, p, beginWord, tmp);
                return ret;
            }
        }

        return {};
    }
};
