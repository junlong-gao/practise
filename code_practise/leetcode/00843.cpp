/*
insight 1:
when we guessed a word, we can use the match count to eliminate other words:
if w matches k character, the word w' does not match w with k char, then w' cannot be the answer (consider both match more than k and match less than k cases)

*/
/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        int l = wordlist.front().size();
	int n = wordlist.size();
	int chances = 10;
	auto match = [&](string &l, string &r) {
		int ret = 0;
		for (int i = 0; i < l.size(); ++i) {
			if (l[i] == r[i]) ret++;
		}
		return ret;
	};
	for (int i = 0; i < chances; ++i) {
		assert(wordlist.size());
	    int idx = rand() % wordlist.size();

		assert(idx != -1);
		int likely = master.guess(wordlist[idx]);
		if (likely == l) return;

		vector<string> t;
		for (int i = 0; i < wordlist.size(); ++i) {
			if ((i != idx) && (match(wordlist[i], wordlist[idx]) == likely)) {
				t.push_back(wordlist[i]);
			}
		}
		swap(t, wordlist);
	}
    }
};

