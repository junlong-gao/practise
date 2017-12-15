//
// Created by Junlong Gao on 7/30/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;
class ValidWordAbbr {
    unordered_map<string, unordered_set<string>> maps;
public:
    ValidWordAbbr(vector<string> &dictionary) {
        for(auto& word: dictionary){
            int length = word.length();
            string abbr = word[0] + to_string(length) + word[length - 1];
            maps[abbr].insert(word);
        }
    }
    bool isUnique(string word) {
        string abbr = word[0] + to_string(word.length()) + word[word.length() - 1];
        if(maps.find(abbr) == maps.end()) return true;
        if(maps[abbr].size() > 1) return false;
        return maps[abbr].find(word) != maps[abbr].end();
    }
};
#endif //PRACTISE_SOLUTION_H
