#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    vector<string> rst;
    void constructor(int loc, string path, const string& s, vector<vector<int>>& n){
        for(auto& next: n[loc]){
            string word = s.substr(loc, next-loc);
            string next_path = (loc == 0)? word: path + string(" ") + word ;
            //cerr << word << " " << next_path << endl;
            if(next == (int)s.length()) rst.push_back(next_path);
            else constructor(next, next_path, s, n);
        }

    }
	vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<vector<int>> n(s.length() + 1);
        for(int i = s.length() - 1; i >= 0; --i){ //[i,s.length)
            if(wordDict.count(s.substr(i, s.length() - i))){
                n[i].push_back(s.length()); //[i,s.length())
            }
        }
        for(int i = s.length() - 1; i >= 0; --i){
            if(n[i].empty()) continue;
            for(int j = i-1; j >=0; --j){ //[j, i)
                if(wordDict.count(s.substr(j, i-j))){
                    //cerr << j << " " << i << " " << endl ;
                    n[j].push_back(i);
                }
            }
        }
        constructor(0, "", s, n);
		return rst;
	}
};

int main(int argc, const char * argv[]) {
    unordered_set<string> wordDict;
    string s = "catsanddog";
    wordDict.insert("cat");
    wordDict.insert("cats");
    wordDict.insert("and");
    wordDict.insert("sand");
    wordDict.insert("dog");
    Solution mysolution;
    auto rst = mysolution.wordBreak(s,wordDict);
    for(auto & it: rst){
        cout << it << endl;
    }
    return 0;
}
