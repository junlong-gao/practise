//
// Created by Junlong Gao on 8/21/16.
//

#ifndef PRACTISE_FENWICKS_H
#define PRACTISE_FENWICKS_H
#include <vector>
#include "catch.hpp"

namespace trees{
    using namespace std;
    class fenwicks_2d{
        vector<vector<int>> tree;
        vector<vector<int>> grid;
    public:
        fenwicks_2d(vector<vector<int>> grid){
            tree.resize(grid.size() , vector<int>(grid[0].size() , 0));
            this->grid.resize(tree.size() , vector<int>(tree[0].size() , 0));
            for(int x = 0; x < grid.size(); ++x){
                for(int y = 0; y < grid[x].size(); ++y){
                    update(x, y, grid[x][y]);
                }
            }
            this->grid = grid;
        }

        void update(int _x, int _y, int _val){
            int val = _val - grid[_x][_y];
            for(int x = _x + 1; x <= tree.size(); x += x & (-x)){
                for(int y = _y + 1; y <= tree[0].size(); y += y & (-y)){
                    tree[x-1][y-1] += val;
                }
            }
        }
        int query(int _x, int _y){
            int ret = 0;
            for(int x = _x; x > 0; x -= x & (-x)){
                for(int y = _y; y > 0; y -= y & (-y)){
                    ret += tree[x-1][y-1];
                }
            }
            return ret;
        }
    };
    TEST_CASE("fenwicks"){
        SECTION("simple"){
            fenwicks_2d ftree({
                                      {1,2},
                                      {3,4}
                              });
            REQUIRE(ftree.query(2, 2) == 10);
            ftree.update(0,0,4);
            REQUIRE(ftree.query(2, 2) == 13);
            REQUIRE(ftree.query(1, 2) == 6);
            REQUIRE(ftree.query(2, 1) == 7);
            REQUIRE(ftree.query(1, 1) == 4);
        }
    }
}
#endif //PRACTISE_FENWICKS_H
