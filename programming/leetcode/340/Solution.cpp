//
// Created by Junlong Gao on 8/5/16.
//

#include "Solution.h"
#include<cassert>

int main(){
    Solution testObj;
    assert(testObj.lengthOfLongestSubstringKDistinct("aabbcc", 2) == 4);
    assert(testObj.lengthOfLongestSubstringKDistinct("aa", 1) == 2);
    assert(testObj.lengthOfLongestSubstringKDistinct("aba", 1) == 1);
    assert(testObj.lengthOfLongestSubstringKDistinct("aa", 0) == 0);
}