class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> bag(wordList.begin(), wordList.end());

        if (bag.count(endWord) == 0) return 0;
        if (endWord == beginWord) return 1;

        int dist = 1;
        vector<string> q {beginWord};
        bag.erase(beginWord);
        while(q.size() > 0) {
            vector<string> next;
            for (auto word : q) {
                for (int i = 0; i < word.size(); ++i) {
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (word[i] == c) continue;
                        swap(word[i], c);
                        if (bag.count(word) == 1) {
                            bag.erase(word);
                            if (word == endWord) {
                                return dist + 1;
                            }
                            next.push_back(word);
                        }
                        swap(word[i], c);
                    }
                }
            }

            dist++;
            swap(q, next);
        }

        return 0;
    }
};
