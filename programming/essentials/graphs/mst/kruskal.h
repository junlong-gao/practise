//
// Created by Junlong Gao on 8/19/16.
//

#ifndef PRACTISE_KRUSKAL_H
#define PRACTISE_KRUSKAL_H

#include <vector>
#include "catch.hpp"
#include "../union_find/union_find.h"

namespace mst{
    struct edge{
        int u, v, w;
        edge(int u, int v, int w):u(u), v(v), w(w){;}
    };
    int kruskal_mst(std::vector<std::vector<int>> G){
        union_find::union_find set(G.size());
        std::vector<edge> edges;
        for(int i = 0; i < G.size(); ++i){
            for(int j = i + 1; j < G[i].size(); ++j){
                edges.emplace_back(i, j, G[i][j]);
            }
        }
        sort(edges.begin(), edges.end(),
             [&](const edge& l, const edge& r){
            return l.w < r.w;
        });
        int ret = 0;
        for(int i = 0; i < edges.size(); ++i){
            if(!set.isSame(edges[i].u, edges[i].v)){
                set.link(edges[i].u, edges[i].v);
                ret += edges[i].w;
            }
        }
        return ret;
    };
    TEST_CASE("smoke test for kruskal"){
        const int infty = std::numeric_limits<int>::max();
        SECTION("simple"){
            auto rst = kruskal_mst({
                                        {infty, 2, 2, 2},
                                        {2, infty, 2, 2},
                                        {2, 2, infty, 2},
                                        {2, 2, 2, infty},
                                });
            REQUIRE(rst == 6);
        }
        SECTION("simple 2"){
            auto rst = kruskal_mst({
                                        {infty, 1, 2, 2},
                                        {1, infty, 1, 1},
                                        {2, 1, infty, 2},
                                        {2, 1, 2, infty},
                                });
            REQUIRE(rst == 3);
        }
    }

}
#endif //PRACTISE_KRUSKAL_H
