//
// Created by Junlong Gao on 8/6/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
       unordered_map<int, int> m;
       vector<int> ret;
       for(int i = 0; i < nums; ++i){
           if(m.find(target - nums[i]) != m.end()){
               return {m[target-nums[i]], i};
           }else{
               m[nums[i]] = i;
           }
       }
       return ret;
    }
};


#endif //PRACTISE_SOLUTION_H
