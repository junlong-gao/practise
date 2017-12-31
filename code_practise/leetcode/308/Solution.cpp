//
//  Solution.cpp
//  practise
//
//  Created by Junlong Gao on 7/30/16.
//  Copyright © 2016 Junlong Gao. All rights reserved.
//

#include "Solution.hpp"
#include <iostream>
#include <cassert>
#include <vector>


int main(){
    vector<vector<vector<int>>> nums = {
        {
            {3, 0, 1, 4, 2},
            {5, 6, 3, 2, 1},
            {1, 2, 0, 1, 5},
            {4, 1, 0, 1, 7},
            {1, 0, 3, 0, 5}
        },
        {
            {2, 4},
            {-3, 5}
        }
    };
    NumMatrix testObj(nums[0]);
    assert(testObj.sumRegion(0, 1, 2, 3) == 19);
    testObj.update(1,2,10);
    assert(testObj.sumRegion(1, 2, 3, 4) == 27);
    
    NumMatrix testObj1(nums[1]);
    testObj1.update(0,1,3);
    testObj1.update(1,1,-3);
    testObj1.update(0,1,1);
    assert(testObj1.sumRegion(0, 0, 1, 1) == -3);
    
}