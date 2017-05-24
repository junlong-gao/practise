//
//  main.cpp
//  Trapping Rain Water
//
//  Created by 骏龙 高 on 9/27/15.
//  Copyright © 2015 Aurora. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;




class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size()<=2) {
            return 0;
        }
        int left = 0; int right = height.size() - 1;
        int maxLeft = height[0]; int maxRight = height[height.size()-1];
        int rst=0;
        while (left<=right) {
            if (height[left]<=height[right]) {
                //whenever we enter here we maintain maxLeft <= height right
                if (height[left]>=maxLeft) {
                    maxLeft=height[left];
                }else{
                    rst = rst + maxLeft - height[left];
                }
                left++;
            }else{
                //whenever we enter here we maintain maxRight <= height left
                if (height[right]>=maxRight) {
                    maxRight=height[right];
                }else{
                    rst = rst + maxRight - height[right];
                }
                right--;
            }
        }
        
        return rst;
    }
};
int main(int argc, const char * argv[]) {
    Solution mine;
    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
    mine.trap(height);
    std::cout << "Hello, World!\n";
    return 0;
}
