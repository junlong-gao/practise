//
// Created by jerry on 2016/8/14.
//

#ifndef PRACTISE_SOLUTION_H
#define PRACTISE_SOLUTION_H
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <iostream>
#include "catch.hpp"

namespace{
    using namespace std;
    class Solution{
    public:
        using vertex_t =vector<int>;
        using edge_t = unordered_map<int, unordered_set<int>>;
        int sum = 0;
        vector<int> solve(vector<int>& cities, unordered_map<int, unordered_set<int>>& edges){
            for(int i = 0; i < cities.size(); ++i){
                sum += cities[i];
            }
            vector<bool> visited(cities.size(), false);
            vector<int> maxs(cities.size(),0);
            visited[0] = true;
            enter(false, 0, cities, edges, visited, maxs);

            return maxs;
        }
        int enter(bool flag, int current, vertex_t& cities, edge_t& edges, vector<bool>& visited, vector<int>& maxs){
            int flow = 0;
            for(auto c: edges[current]){
                if(!visited[c]){
                    visited[c] = true;
                    int rst = enter(true, c, cities, edges, visited, maxs);
                    flow += rst;
                    maxs[current] = max(maxs[current], rst);
                }
            }
            if(flag){
                maxs[current] = max(maxs[current], sum - cities[current] - flow);
            }
            return cities[current] + flow;
        }
    };

    TEST_CASE("smoke testing"){
        Solution s;
        SECTION("sample"){
            vector<int> cities = {1,2,5,4,3};

            unordered_map<int, unordered_set<int>> edges {
                    {0, unordered_set<int>({2})},
                    {1, unordered_set<int>({2})},
                    {2, unordered_set<int>({0,1,3,4})},
                    {3, unordered_set<int>({2})},
                    {4, unordered_set<int>({2})}
            };
            auto rst = s.solve(cities, edges);
            REQUIRE(rst[0] == 14);
        }
        SECTION("sample 2"){
            vector<int> cities = {1,2,3,4,5,7,15};

            unordered_map<int, unordered_set<int>> edges {
                    {0, unordered_set<int>({4})},
                    {1, unordered_set<int>({4,5,6})},
                    {2, unordered_set<int>({4})},
                    {3, unordered_set<int>({4})},
                    {4, unordered_set<int>({0,1,2,3})},
                    {5, unordered_set<int>({1})},
                    {6, unordered_set<int>({1})}
            };
            auto rst = s.solve(cities, edges);
            REQUIRE(rst[0] == 36);
            REQUIRE(rst[1] == 15);
            REQUIRE(rst[2] == 34);
            REQUIRE(rst[3] == 33);
            REQUIRE(rst[4] == 24);
            REQUIRE(rst[5] == 30);
            REQUIRE(rst[6] == 22);
        }

    }

}
#endif //PRACTISE_SOLUTION_H
