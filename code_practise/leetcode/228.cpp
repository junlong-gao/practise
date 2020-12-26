//
// Created by Junlong Gao on 7/30/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include<vector>
#include <string>

using namespace std;


class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int i = 0;
        vector<string> ans;
        while(i < nums.size()){
            int j = i + 1;
            while(j < nums.size() && nums[j] == nums[j-1] + 1) j++;
            if(j-1 > i){
                ans.push_back(to_string(nums[i]) + "->" + to_string(nums[j-1]));
            }else{
                ans.push_back((to_string(nums[i])));
            }
            i = j;
        }
        return ans;
    }
};


#endif //PRACTISE_SOLUTION_H
