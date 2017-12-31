//
//  main.cpp
//  Product of Array Except Self
//
//  Created by 骏龙 高 on 9/27/15.
//  Copyright © 2015 Aurora. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        
        vector<int> rst(nums.size(),1);
        if (nums.size()<1) {
            return rst;
        }
        if (nums.size()==1) {
            rst[0]=nums[0];
            return rst;
        }
        
        int front = 1;
        int back = 1;
        int n = nums.size();
        for (int i = 0; i < nums.size(); i++) {
            rst[i] = rst[i]*front;
            front = nums[i]*front;
            rst[n-1-i] = rst[n-1-i]*back;
            back = nums[n-1-i]*back;
        }
        
        return rst;
    }
};

int main(int argc, const char * argv[]) {
    vector<int> t ={1,2,3};
    Solution mysolutions;
    mysolutions.productExceptSelf(t);
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
