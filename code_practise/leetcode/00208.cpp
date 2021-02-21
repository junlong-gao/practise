class Trie {
    unordered_map<char, Trie*> children;
    bool isWord {false};
    void add(string &word, int idx) {
        if (idx == word.size()) {
            isWord = true;
            return;
        }
        if (children.count(word[idx]) == 0) {
            children[word[idx]] = new Trie;
        }
        children[word[idx]]->add(word, idx + 1);
    }
    
    Trie *find(string &w) {
        Trie *cur = this;
        int idx = 0;
        while (idx < w.size() && cur->children.count(w[idx])) {
            cur = cur->children[w[idx]];
            idx++;
        }
        
        if (idx == w.size()) {
            return cur;
        }
        return nullptr;
    }
public:
    ~Trie() {
        for (auto pr : children) {
            delete pr.second;
        }
    }
    /** Initialize your data structure here. */
    Trie() {
        
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
       add(word, 0);
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
       Trie *node = find(word);
        if (node == nullptr) {
            return false;
        }
        return node->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
       return find(prefix) != nullptr; 
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */