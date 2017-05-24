//
// Created by Junlong Gao on 8/7/16.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include <vector>

using namespace std;
class Solution {
public:
    int candy(vector<int>& ratings) {
        int ret = 0;
        vector<int> candies(ratings.size(), 0);
        candies[0] = 0;
        for(int i = 1; i < ratings.size(); ++i){
            if(ratings[i] > ratings[i-1]){
                candies[i] = candies[i-1] + 1;
            }else{
                candies[i] = 1;
            }
        }
        candies[ratings.size() - 1] = max(1,candies[ratings.size() - 1]);
        for(int i = ratings.size() - 2; i >= 0; --i){
            if(ratings[i] > ratings[i+1]){
                candies[i] = max(candies[i+1] + 1, candies[i+1]);
            }else{
                candies[i] = max(1, candies[i]);
            }
        }
        for(int i = 0; i < candies.size(); ++i){
            ret += candies[i];
        }
        return ret;
    }
};

#endif //PRACTISE_SOLUTION_H
