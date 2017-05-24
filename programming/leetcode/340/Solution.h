//
// Created by Junlong Gao on 8/5/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include<vector>
#include<unordered_map>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> m;
        int curBest = 0;
        int i = 0, j = 0;
        while (j < s.length()) {
            while (j < s.length()) {
                m[s[j]] ++;
                if(m.size() > k) break;
                j++;
            }
            curBest = max(curBest, j - i);
            if(j >= s.length()) break;
            while(i <= j){
                if(m[s[i]] > 0) m[s[i]] --;
                if(m[s[i]] == 0) m.erase(s[i]);
                i++;
                if(m.size() <= k) break;
            }
            j++;
        }
        return curBest;
    }
};


#endif //PRACTISE_SOLUTION_H
