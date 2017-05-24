#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
    class TrieNode {
        
    public:
        unordered_map<char, TrieNode*> children;
        bool isWord;
        // Initialize your data structure here.
        TrieNode() {
            
        }
    };
    
    class Trie {
    public:
        Trie() {
            root = new TrieNode();
        }
        
        void insert_helper(string& word, int pos, TrieNode* node){
            if(pos == word.length()){
                node->isWord = true;
                return;
            }
            if(node->children.find(word[pos])==node->children.end()){
                node->children[word[pos]] = new TrieNode();
            }
            insert_helper(word, pos+1, node->children[word[pos]]);
        }
        
        // Inserts a word into the trie.
        void insert(string word) {
            insert_helper(word, 0, root);
        }
        
        bool search_helper(string& word, int pos, TrieNode* node){
            if(pos == word.length()){
                return node->isWord;
            }
            if(node->children.find(word[pos]) == node->children.end()){
                return false;
            }
            return search_helper(word, pos+1, node->children[word[pos]]);
        }
        // Returns if the word is in the trie.
        bool search(string word) {
            return search_helper(word, 0, root);
        }
        
        
        bool startsWith_helper(string& word, int pos, TrieNode* node){
            if(pos == word.length()){
                return true;
            }
            if(node->children.find(word[pos]) == node->children.end()){
                return false;
            }
            return startsWith_helper(word, pos+1, node->children[word[pos]]);
        }
        // Returns if there is any word in the trie
        // that starts with the given prefix.
        bool startsWith(string prefix) {
            return startsWith_helper(prefix, 0, root);
        }
        
    private:
        TrieNode* root;
    };

	TEST_CASE("tests"){
		Trie testObj;
		SECTION("sample"){
            testObj.insert("ab");
            REQUIRE(!testObj.search("a"));
            REQUIRE(testObj.startsWith("a"));
		}
	}
}


