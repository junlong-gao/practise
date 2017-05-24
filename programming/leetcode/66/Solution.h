//
// Created by Junlong Gao on 7/30/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include <vector>
#include <algorithm>

using namespace std;
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        vector<int> ans;
        for(int i = digits.size() - 1; i >= 0; --i){
            ans.push_back((digits[i] + carry)%10);
            carry = (digits[i] + carry)/10;
        }
        if(carry){
            ans.push_back(carry);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

#endif //PRACTISE_SOLUTION_H
