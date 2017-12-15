//
// Created by Junlong Gao on 8/30/16.
//
#include <unordered_set>
#include <vector>
#include "catch.hpp"

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
namespace lee128{
    using namespace std;
    class Solution {
    public:
        int longestConsecutive(vector<int>& nums) {
            unordered_set<int> table(nums.begin(), nums.end());
            int n = 0, m = 0;
            int cur = numeric_limits<int>::min();
            for(auto k : table){
                if(table.find(k - 1) == table.end()){
                    m = k+1;
                    while(table.find(m) != table.end()){
                        m++;
                    }
                    cur = max(cur, m - k);
                }
            }
            return cur;
        }
    };

    TEST_CASE("smoke") {
        Solution testObj;
        SECTION("sample 0") {
            vector<int> testcase = {100, 4, 200, 1, 3, 2};
            REQUIRE(testObj.longestConsecutive(testcase) == 4);
        }
    }
}
#endif //PRACTISE_SOLUTION_H
