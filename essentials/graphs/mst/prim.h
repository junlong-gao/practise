//
// Created by Junlong Gao on 8/19/16.
//

#ifndef PRACTISE_PRIM_H_H
#define PRACTISE_PRIM_H_H

#include "../priority_queue/heap.h"
#include "catch.hpp"
#include <vector>

namespace mst{
    std::pair<int, std::vector<int>> prim_mst(std::vector<std::vector<int>> G){
        std::vector<int> key;
        std::vector<int> p;
        std::vector<bool> visited;
        priority_queue::binary_heap<int> Q([&](int l, int r){
            return key[l] > key[r];
        });
        key.push_back(0);
        Q.push(0);
        p.push_back(0);
        for(int i = 1; i < G.size(); ++i){
            p.push_back(-1);
            visited.push_back(false);
            key.push_back(std::numeric_limits<int>::max());
            Q.push(i);
        }
        int ret = 0;
        while(!Q.empty()){
            int v = Q.top();
            Q.pop();
            visited[v] = true;
            ret += key[v];
            for(int i = 0; i < G[v].size(); ++i){
                if(!visited[i] && G[v][i] >= 0 && G[v][i] < key[i]){
                    key[i] = G[v][i];
                    p[i] = v;
                }
            }
            Q.update_keys(); //this is a waste of time
        }
        return make_pair(ret, p);
    };

    TEST_CASE("smoke test prim"){
        const int infty = std::numeric_limits<int>::max();

        SECTION("simple"){
            auto rst = prim_mst({
                                        {infty, 2, 2, 2},
                                        {2, infty, 2, 2},
                                        {2, 2, infty, 2},
                                        {2, 2, 2, infty},
                                });
            REQUIRE(rst.first == 6);
            REQUIRE(rst.second[0] == 0);
            REQUIRE(rst.second[1] == 0);
            REQUIRE(rst.second[2] == 0);
            REQUIRE(rst.second[3] == 0);
        }
        SECTION("simple 2"){
            auto rst = prim_mst({
                                        {infty, 1, 2, 2},
                                        {1, infty, 1, 1},
                                        {2, 1, infty, 2},
                                        {2, 1, 2, infty},
                                });
            REQUIRE(rst.first == 3);
            REQUIRE(rst.second[0] == 0);
            REQUIRE(rst.second[1] == 0);
            REQUIRE(rst.second[2] == 1);
            REQUIRE(rst.second[3] == 1);
        }
    }
}

#endif //PRACTISE_PRIM_H_H
