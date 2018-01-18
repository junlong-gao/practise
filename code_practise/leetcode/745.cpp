class WordFilter {
  
    struct Trie {
        unordered_map<char, Trie*> children;
        vector<int> indexes;
        void _add(const string& word, int index, int sofar) {
            
            indexes.push_back(index);
            
            if (sofar == word.length()) {
                return;
            }
            
            if (children.count(word[sofar]) == 0) {
               children[word[sofar]] = new Trie; 
            }
            
            children[word[sofar]]->_add(word, index, sofar + 1);
        }
        
        void add(const string& word, int index) {
            _add(word, index, 0);
        }
        
        vector<int>& _get(const string& prefix, int sofar, bool& found) {
            if (prefix.length() == sofar) {
                found = true;
                return indexes;
            }
            if (children.count(prefix[sofar]) == 0) {
                found = false;
                return indexes;
            }
            return children[prefix[sofar]]->_get(prefix, sofar + 1, found);
        }
        
        vector<int>& get(const string& prefix, bool& found) {
            return _get(prefix, 0, found);
        }
    };
    
    Trie prefixT, suffixT;
    vector<string>& words;
public:
    WordFilter(vector<string> words):words(words) {
       for (int i = 0; i < words.size(); ++i) {
           prefixT.add(words[i], i);
           reverse(words[i].begin(), words[i].end());
           suffixT.add(words[i], i);
       }
       return;   
    }
    
    int f(string prefix, string suffix) {
        bool prefixFound = false, suffixFound = false;
        auto & p = prefixT.get(prefix, prefixFound);
        if (!prefixFound) {
            return -1;
        }
        reverse(suffix.begin(), suffix.end());
        auto & s = suffixT.get(suffix, suffixFound);

        if(!suffixFound) {
            return -1;
        }
        
        int i = p.size() - 1, j = s.size() - 1;

        while (i >= 0 && j >= 0) {
            if (p[i] == s[j]) {
                return p[i];
            }
            if (p[i] > s[j]) {
                i--;
            } else {
                j--;
            }
        }
        
        return -1;
    }
};

/*
need a faster solution for this
*/
