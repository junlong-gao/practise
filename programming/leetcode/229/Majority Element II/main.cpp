//
//  main.cpp
//  Majority Element II
//
//  Created by 骏龙 高 on 9/22/15.
//  Copyright © 2015 Aurora. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> rst;
        int cand1=0,cand2=0,c1=0,c2=0;
        
        for(auto n: nums){
            if (c1>0&&c2>0) {
                if (n == cand1) {
                    c1++;
                }else if(n== cand2){
                    c2++;
                }else{
                    c1--;c2--;
                }
            }else if(c1>0&&c2==0){
                if (n == cand1) {
                    c1++;
                }else{
                    cand2= n;c2=1;
                }
            }else if(c1==0&c2>0){
                if (n==cand2) {
                    c2++;
                }else{
                    cand1=n;c1++;
                }
            }else{
                cand1=n;c1=1;
            }
        }
        c1=c2=0;
        for(auto n : nums){
            if (n == cand1) {
                c1++;
            }else if (n == cand2){
                c2++;
            }
        }
        if (c1>nums.size()/3) {
            rst.push_back(cand1);
        }
        if (c2>nums.size()/3) {
            rst.push_back(cand2);
        }
        return rst;
    }
};

int main(int argc, const char * argv[]) {
    vector<int> test = {1,4,3,4,3};
    Solution mysolution;
    auto rst = mysolution.majorityElement(test);
    for(auto n : rst){
        cout<<n<<" ";
    }
    cout<<endl;
    return 0;
}
