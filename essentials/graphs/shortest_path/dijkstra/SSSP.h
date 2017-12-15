//
// Created by Junlong Gao on 8/19/16.
//

#ifndef PRACTISE_SSSP_H
#define PRACTISE_SSSP_H
#include <vector>
#include "../priority_queue/heap.h"
#include "catch.hpp"

namespace dijkstra{
    std::pair<std::vector<int>, std::vector<int>> SSSP(std::vector<std::vector<int>> G, int source){
        std::vector<int> p;
        std::vector<int> key;
        int infty = std::numeric_limits<int>::max();
        priority_queue::binary_heap<int> Q([&](const int l, const int r){
            return key[l] > key[r];
        });
        for(int i = 0; i < G.size(); ++i){
            Q.push(i);
            p.push_back(-1);
            key.push_back(infty);
        }
        p[source] = source;
        key[source] = 0;
        Q.update_keys();
        while(Q.size() > 1){
            int v = Q.top();
            Q.pop();
            for(int i = 0; i < G[v].size(); ++i){
                assert(key[v] != infty);
                std::cout << i << " " << G[v][i] << " " << key[v] << std::endl;
                if(G[v][i] >= 0 &&
                    ((G[v][i] < infty && key[v] < infty) && //in case of overflow
                        G[v][i] + key[v] < key[i])){
                    key[i] = key[v] + G[v][i];
                    p[i] = v;
                }
            }
            Q.update_keys();
        }
        return make_pair(p, key);
    };
    TEST_CASE("smoke test for SSSP"){
        int infty = std::numeric_limits<int>::max();
        SECTION("simple"){
            auto rst = SSSP({
                                        {infty, 1, 10, 10},
                                        {10, infty, 2, 10},
                                        {11, 11, infty, 2},
                                        {11, 11, 11, infty},
                                }, 0);
            REQUIRE((rst.first[0] == 0));
            REQUIRE((rst.second[0] == 0));

            REQUIRE((rst.first[1] == 0));
            REQUIRE((rst.second[1] == 1));

            REQUIRE((rst.first[2] == 1 ));
            REQUIRE((rst.second[2] == 3));

            REQUIRE((rst.first[3] == 2 ));
            REQUIRE((rst.second[3] == 5));
        }
    }
}
#endif //PRACTISE_SSSP_H
