//
//  main.cpp
//  3Sum Closest
//
//  Created by John on 9/14/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:
    int abs(int x){
        return (x>0)?x:(-x);
    }
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int cand = 0;
        unsigned int sofar = INT32_MAX;
        for (int i = 0; i < nums.size(); i++) {
            int tmp = target - nums[i];
            
            int front = i + 1;
            int back = nums.size() - 1;
            while (front < back) {
                int sum = nums[front] + nums[back];
                int cur = abs(sum - tmp);
                if (cur<sofar) {
                    if (cur == 0) {
                        return sum + nums[i];
                    }
                    sofar = abs(sum - tmp);
                    cand = sum + nums[i];
                }
                if (sum > tmp) {
                    back--;
                }else {
                    front++;
                }
            }
            
        }
        return cand;
    }
};
int main(int argc, const char * argv[]) {
    Solution mysolutions;
    
    vector<int> num{1,1,1,0};
    int target = -100;
    
    mysolutions.threeSumClosest(num, target);
    
    return 0;
}
