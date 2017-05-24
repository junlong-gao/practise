//
//  main.cpp
//  3Sum Smaller
//
//  Created by John on 9/14/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int counter = 0;
        sort(nums.begin(), nums.end());
        for (auto i = 0 ; i < nums.size(); i ++) {
            int front = i + 1;
            auto back = nums.size()-1;
            while (front < back) {
                if (nums[i]+nums[front]+nums[back] >= target) {
                    back -- ;
                }else{
                    counter += back-front;
                    front ++;
                }
            }
        }
        return counter;
    }
};

int main(int argc, const char * argv[]) {
    vector<int> v{1,-1};
    
    Solution mysolutions;
    mysolutions.threeSumSmaller(v, 0);
    
    return 0;
}
