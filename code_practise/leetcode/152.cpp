//
//  main.cpp
//  Maximum Product Subarray
//
//  Created by 骏龙 高 on 9/27/15.
//  Copyright © 2015 Aurora. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.size()<1) {
            return 0;
        }
        if (nums.size() ==1) {
            return nums[0];
        }
        int maxProd = nums[0];
        int minProd = nums[0];
        
        int max = maxProd;
        for (int i = 1; i < nums.size(); i++) {
            
            if (nums[i]<0) {
                swap(maxProd, minProd);
            }
            maxProd = my_max(nums[i],maxProd*nums[i]);
            minProd = my_min(nums[i],minProd*nums[i]);
            max = maxProd>max?maxProd:max;
        }

        return max;
    }
    inline void swap(int &x, int &y){
        int t = x;
        x = y; y =t;
    }
    inline int my_max(int x, int y){
        return x>y?x:y;
    }
    inline int my_min(int x, int y){
        return x<y?x:y;
    }
};

int main(int argc, const char * argv[]) {
    Solution mysolutions;
    vector<int> t = {-2,3,-4};
    mysolutions.maxProduct(t);
    return 0;
}
