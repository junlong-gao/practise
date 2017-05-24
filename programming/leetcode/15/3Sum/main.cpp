//
//  main.cpp
//  3Sum
//
//  Created by John on 9/13/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> rst;
        for (auto i  = 0; i < nums.size(); i++) {
            int front = i + 1;
            int back = nums.size() - 1;
            int target = - nums[i];
            while (front < back) {
                int sum = nums[front] + nums[back];
                if (sum > target) {
                    back -- ;
                } else if (sum < target){
                    front ++ ;
                } else {
                    vector<int> triplet(3, 0);
                    triplet[0] = nums[i];
                    triplet[1] = nums[front];
                    triplet[2] = nums[back];
                    rst.push_back(triplet);
                    while (front < back && nums[front] == triplet[1]) {
                        front++;
                    }
                    while (front < back && nums[back] == triplet[2]) {
                        back--;
                    }
                }
               
                
            }
            while (i + 1 < nums.size() && nums[i + 1] == nums[i])
                i++;
        }
        return rst;
    }
    
};

int main(int argc, const char * argv[]) {
    Solution mysolutions;
    vector<int> nums;
    nums.push_back(-1);
    nums.push_back(0);

    nums.push_back(1);

    nums.push_back(2);

    nums.push_back(-1);
    nums.push_back(-4);

    mysolutions.threeSum(nums);
    return 0;
}
