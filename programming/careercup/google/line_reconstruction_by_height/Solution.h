//
// Created by jerry on 2016/8/14.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include <vector>
#include <algorithm>
#include "catch.hpp"

namespace{
    using namespace std;
    using pairs = vector<pair<int, int>>;
    class Solution{
    public:
        void solution(pairs& line){
            sort(line.begin(), line.end(), [&](const pair<int,int> l, const pair<int,int> r){
               if(l.first != r.first) return l.first > r.first;
                return l.second < r.second;
            });
            for(int i = 1; i < line.size(); ++i){
                int num = i - line[i].second;
                for(int j = i; j - 1 >= 0 && num > 0; --j, --num){
                    swap(line[j], line[j-1]);
                }
            }
        }

    };
    TEST_CASE("smoke test"){
        Solution s;
        SECTION("sample"){
            pairs sample { {7,0}, {4,4},{7,1}, {5,0}, {6,1},{5,2} };
            s.solution(sample);
            REQUIRE(sample[0] == make_pair(5, 0));
            REQUIRE(sample[1] == make_pair(7, 0));
            REQUIRE(sample[2] == make_pair(5, 2));
            REQUIRE(sample[3] == make_pair(6, 1));
            REQUIRE(sample[4] == make_pair(4, 4));
            REQUIRE(sample[5] == make_pair(7, 1));
        }
        SECTION("sample 2"){
            pairs sample { {7,0}, {7,1}, {7,2}};
            s.solution(sample);
            REQUIRE(sample[0] == make_pair(7, 0));
            REQUIRE(sample[1] == make_pair(7, 1));
            REQUIRE(sample[2] == make_pair(7, 2));
        }
    }
}

#endif //PRACTISE_SOLUTION_H
