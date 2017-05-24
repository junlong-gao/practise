//
//  main.cpp
//  Word Break
//
//  Created by John on 9/27/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
	bool wordBreak(string s, unordered_set<string>& wordDict) {
		if (wordDict.size()==0) {
			return false;
		}
		
		vector<bool> f(s.size()+1,false);
		
		f[0]=true; //first 0 words, empty string, will always be in the dict
		
		
		for (int i = 1; i < s.size()+1; i++) {
			for (int j = i - 1; j >=0; j--) {
				if (f[j]) {
					string word = s.substr(j,i-j);
					if (wordDict.find(word)!=wordDict.end()) {
						f[i] = true;
						break;//the i is set, get out of the inner search for next i
					}
				}
			}
		}
		return f[s.size()];
	}
};
int main(int argc, const char * argv[]) {
	
	Solution mine;
	unordered_set<string> wordDict;
	wordDict.insert("leet");
	wordDict.insert("code");
	
	string s = "leetcode";
	mine.wordBreak(s, wordDict);
	// insert code here...
	std::cout << "Hello, World!\n";
    return 0;
}
