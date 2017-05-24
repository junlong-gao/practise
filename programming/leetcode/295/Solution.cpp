//
// Created by junlong on 8/3/16.
//

#include "Solution.h"
#include <cassert>

int main(){

    MedianFinder testObj;
    testObj.addNum(1);
    assert(testObj.findMedian() == 1);
    testObj.addNum(2);
    assert(testObj.findMedian() == 1.5);
    testObj.addNum(3);
    assert(testObj.findMedian() == 2);
    testObj.addNum(0);
    assert(testObj.findMedian() == 1.5);
    testObj.addNum(0);
    assert(testObj.findMedian() == 1);
    testObj.addNum(0);
    assert(testObj.findMedian() == 0.5);
    return 0;
}