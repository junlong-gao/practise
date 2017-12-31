//
//  main.cpp
//  Maximum Subarray
//
//  Created by John on 9/26/15.
//  Copyright © 2015 John. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public: int maxSubArray(vector<int>& nums) { 
	int s[nums.size()]; 
	int max = s[0] = nums[0]; 
	for (int i = 1; i < nums.size(); i++) {
		s[i] = s[i-1] > 0 ? (nums[i] + s[i-1]) : nums[i]; 
		max = std::max(max, s[i]); 
	}
	return max;
}
};

int main(int argc, const char * argv[]) {
	vector<int> test = {-2,1,-3,4,-1,2,1,-5,4};
	vector<int> test2 = {-2,1};
	vector<int> test3 = {-2};
	vector<int> test4 = {1,-2};
	vector<int> test5 = {1,2};
	Solution mysolution;
	mysolution.maxSubArray(test5);
    return 0;
}
