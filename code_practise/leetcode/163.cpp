//
// Created by Junlong Gao on 7/30/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> ans;
        int l = lower - 1;
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i]-1 > l + 1){
                ans.push_back(to_string(l+1) + "->" + to_string(nums[i] - 1));
            }
            if(nums[i] - 1 == l + 1){
                ans.push_back(to_string(l+1));
            }
            l = nums[i];
        }
        if(upper > l + 1){
            ans.push_back(to_string(l+1) + "->" + to_string(upper));
        }
        if(upper == l + 1){
            ans.push_back(to_string(l+1));
        }
        return ans;
    }
};


#endif //PRACTISE_SOLUTION_H
