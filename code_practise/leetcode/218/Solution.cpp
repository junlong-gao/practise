//
//  Solution.cpp
//  practise
//
//  Created by Junlong Gao on 7/31/16.
//  Copyright © 2016 Junlong Gao. All rights reserved.
//

#include "Solution.hpp"
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

int main(){
    Solution test;
    vector<vector<int>> buildings = {
        {0, 3, 3},
        {1, 4, 3},
        {2, 5, 3},
        {3, 6, 3},
    };
    auto rst = test.getSkyline(buildings);
    for(auto p : rst){
        cout << "(" << p.first << "," << p.second << ") ";
    }
    
}