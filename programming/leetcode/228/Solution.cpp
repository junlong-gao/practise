//
// Created by Junlong Gao on 7/30/16.
//

#include <cassert>
#include "Solution.h"

bool testEqual(vector<string>&& out, vector<string>& expected){
    if(out.size()!=expected.size()) return false;
    for(int i = 0; i < out.size(); ++i){
        if(out[i] != expected[i]) return false;
    }
    return true;
}
int main(){
    Solution testObj;
    vector<int> nums = {0,1,2,4,5,7};
    vector<string> expected = {"0->2", "4->5", "7"};
    assert(testEqual(testObj.summaryRanges(nums), expected));
}

