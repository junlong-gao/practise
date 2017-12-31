//
// Created by Junlong Gao on 8/2/16.
//

#include "Solution.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(){
    vector<int> v1 = {1,2,3,6};
    vector<int> v2 = {4};

    ZigzagIterator testObj(v1,v2);
    assert(testObj.next() == 1);
    assert(testObj.next() == 4);
    assert(testObj.next() == 2);
    assert(testObj.next() == 3);
    assert(testObj.next() == 6);
    assert(testObj.hasNext() == false);
}