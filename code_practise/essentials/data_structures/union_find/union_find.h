//
// Created by Junlong Gao on 8/19/16.
//

#ifndef PRACTISE_UNION_FIND_H
#define PRACTISE_UNION_FIND_H
#include <vector>
#include "catch.hpp"
namespace union_find{
    class union_find{
        std::vector<int> rank;
        std::vector<int> parent;
    public:
        union_find(int size){
            rank.resize(size);
            parent.resize(size);
            for(int i = 0; i < size; ++i){
                rank[i] = 0;
                parent[i] = i;
            }
        }

        int find(int x){
            if(parent[x] != x){
                parent[x] = find(parent[x]);
                return parent[x];
            }
            return x;
        }

        bool isSame(int x, int y){
            return find(x) == find(y);
        }

        void link(int x, int y){
            if(x >= rank.size() || y >= rank.size()){
                throw std::runtime_error("out of bound");
            }
            x = find(x);
            y = find(y);
            if(rank[x] > rank[y]){
                parent[y] = x;
            }else{
                parent[x] = y;
                if(rank[x] == rank[y]){
                    rank[y] ++;
                }
            }
        }
    };
    TEST_CASE("smoke for union find"){
        SECTION("smoke"){
            union_find set(5);

            REQUIRE(!set.isSame(1,2));
            set.link(1,2);
            REQUIRE(set.isSame(1,2));

            REQUIRE(!set.isSame(3,1));
            set.link(2,3);
            REQUIRE(set.isSame(3,1));

            REQUIRE(!set.isSame(3,4));
            set.link(3,4);
            REQUIRE(set.isSame(3,4));

            REQUIRE(!set.isSame(0,1));
            set.link(0,4);
            REQUIRE(set.isSame(0,1));
        }
    }
}
#endif //PRACTISE_UNION_FIND_H
