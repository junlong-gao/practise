/*
construct a trie
use it to control lookup
for each mismatch char, assume it is the mismatch and search.
 a b c
 a c
 c b

  a b  
*/
class MagicDictionary {
	struct trie {
		bool isWord {false}; // XXX must init
		unordered_map<char, trie*> cs;
		~trie () {
			for (auto &pr : cs) {
				delete pr.second;
			}
		}
		void add(const string & w, int soFar) {
			if (soFar == w.size()) {
				isWord = true;
				return;
			}
			if (cs.count(w[soFar]) == 0) {
				cs[w[soFar]] = new trie;
			}
			cs[w[soFar]]->add(w, soFar+1);
		}

		bool matchAt(const string & w, int soFar) {
			if (soFar == w.size()) return isWord;
/*XXX two issues here
			if (cs.count(w[soFar]) == 0) return false;
			return matchAt(w, soFar + 1);
*/
                   if (cs[w[soFar]] == nullptr) return false
                   return cs[w[soFar]]->matchAt(w, soFar+1);
		}
	} root;

public:
    /** Initialize your data structure here. */
    MagicDictionary() {
        
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
	for (const auto & word : dict) {
		root.add(word, 0);
	}
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
	trie *tmp = &root; int cur = 0;
	while (cur < word.size() && tmp) {
		for (auto & pr : tmp->cs) {
			if (pr.first == word[cur] || pr.second == nullptr) { continue; }
			if (pr.second->matchAt(word, cur + 1)) return true;
		}
		tmp = tmp->cs[word[cur]];
		cur++;
	}
	return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * bool param_2 = obj.search(word);
 */

