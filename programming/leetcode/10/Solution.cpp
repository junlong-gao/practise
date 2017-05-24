//
// Created by Junlong Gao on 8/2/16.
//

#include "Solution.h"
#include <vector>
#include <string>
#include <assert.h>

using namespace std;


int main(){
    Solution testObj;
    string s = "aa";
    string p = "aa";

    assert(testObj.isMatch(s, p));
    assert(testObj.isMatch("aa", ".*"));
    assert(testObj.isMatch("aaa", "a.*"));
    assert(testObj.isMatch("aa", "a*"));
    assert(testObj.isMatch("ab", "a.*"));
    assert(testObj.isMatch("ab", "ab*"));
    assert(testObj.isMatch("aab", "c*a*b"));
    assert(!testObj.isMatch("abcd", "d*"));

}