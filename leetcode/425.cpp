#include <iostream>
#include <cassert>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    class trie {
        unordered_map<char, trie*> children;
    public:
        void _add_word(const string& word, int prefix) {
            if (prefix == word.length()) {
                return;
            }
            if (children.find(word[prefix]) == children.end()) {
                children[word[prefix]] = new trie();
            }
            children[word[prefix]]->_add_word(word, prefix + 1);
        }
        void add_word(const string& word) {
          _add_word(word, 0);
        }
        
        void find_prefix(const string& prefix, vector<string>& rst) {
          string sofar;
          _find_prefix(prefix, rst, 0, sofar);
        }
        void _find_prefix(const string& prefix, vector<string>& rst, int matched, string& sofar) {

          if (matched < prefix.length()) {
            auto next = children.find(prefix[matched]);
            if (next == children.end()) {
              return;
            }
            sofar.push_back(prefix[matched]);
            return next->second->_find_prefix(prefix, rst, matched + 1, sofar);
          }
          
          if (children.empty()) {
            rst.push_back(sofar);
            return;
          }
          
          for(auto cc:children) {
            sofar.push_back(cc.first);
            cc.second->_find_prefix(prefix, rst, matched + 1, sofar);
            sofar.pop_back();
          }
        }
        
        ~trie() {
          for (auto& c: children) {
            delete c.second;
          }
        }
    };
public:
    
    void unit() {
        trie root;
        vector<string> rst;
        string sofar;
        auto expect = vector<string>{"abcd", "abce"};
        root.add_word("abcd");
        root.add_word("abce");
        root.find_prefix("abc", rst);
        sort(rst.begin(), rst.end());
        assert(rst == expect);
        
        rst.clear();
        root.find_prefix("abcf", rst);
        assert(rst.empty());
        rst.clear();
        root.find_prefix("abcde", rst);
        assert(rst.empty());
        
        rst.clear();
        root.add_word("abde");
        root.find_prefix("ab", rst);
        sort(rst.begin(), rst.end());
        expect = vector<string>{"abcd", "abce", "abde"};
        assert(rst == expect);
        
        rst.clear();
        root.find_prefix("abd", rst);
        expect = vector<string>{"abde"};
        sort(rst.begin(), rst.end());
        assert(rst == expect);
    }
    
    void search(vector<string> ws, trie& root, vector<vector<string>>& ret,
    unordered_map<string, int>& count) {
      if (ws.size() == ws.front().length()) {
        ret.push_back(ws);
        return;
      }
      
      string prefix;
      vector<string> words;
      int l = ws.size();
      for (int i = 0; i < l; ++i) {
        prefix.push_back(ws[i][l]);
      }
      root.find_prefix(prefix, words);
      for(auto& w: words) {
        if(count[w] > 0) {
          count[w]--;
          ws.push_back(w);
          search(ws, root, ret, count);
          ws.pop_back();
          count[w]++;
        }
      }
    }
    
    vector<vector<string>> wordSquares(const vector<string>& words) {
      trie root;
      vector<vector<string>> ret;
      unordered_map<string, int> count;
      int l = words.front().length();
      for(auto& w : words) {
        root.add_word(w);
        count[w]++;
      }
      for (auto& w:words) {
        vector<string> ws{w};
        count[w]--;
        search(ws, root, ret, count);
        count[w]++;
      }
     return ret;
    }
};

int main() {
  Solution s;
  auto ret = s.wordSquares({
    "aab",
    "aac",
    "bbb",
    "bce"
  });
  for (auto s: ret) {
    cout << "[";
    for (auto w:s) {
      cout << w <<" ";
    }
    cout << "]"<< endl;
  }
}
