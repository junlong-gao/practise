#include <vector>
#include <iostream>
#include "catch.hpp"

namespace APSP{
	using namespace std;
	using grid = vector<vector<int>>;	
	pair<grid, grid> floyd(grid G){
		int infty = numeric_limits<int>::max();
		grid d = G;
		grid p = grid(G.size(), vector<int>(G.size(), -1));
		for(int i = 0; i < G.size(); ++i){
			for(int j = 0; j < G[i].size(); ++j){
				p[i][j] = j;
			}
		}
		for(int k = 1; k < d.size(); ++k){
			for(int i = 0; i < d.size(); ++i){
				for(int j = 0; j < d[i].size(); ++j){
					if(d[i][k] < infty && d[k][j]<infty&&
						d[i][j] > d[i][k] + d[k][j]){
						d[i][j] = d[i][k] + d[k][j];
						p[i][j] = k;
					}
				}
			}
		}
        return make_pair(d, p);
	}
    void printer(grid& p, int i, int j){
        if(p[i][j] == j){
            cout << i << " ";
        }else{
            printer(p, i, p[i][j]);
            printer(p, p[i][j], j);
        }
    }
	TEST_CASE("smoke floyd"){
        SECTION("simple"){
            auto rst = floyd({
                                     {0, 10, 20, 30},
                                     {1, 0, 2, 3},
                                     {15, 5, 0, 17},
                                     {10, 7, 5, 0}
                             });
            grid expect = {
                    {0, 10, 12, 13},
                    {1, 0, 2, 3},
                    {6, 5, 0, 8},
                    {8, 7, 5 ,0}
            };
            for(int i = 0; i < rst.first.size(); ++i){
                for(int j = 0; j < rst.first[i].size(); ++j){
                    cout << endl <<"the path of " << i << " -> " << j << " is: " << endl;
                    printer(rst.second, i, j);
                    cout << j << endl;
                    std::cout << "which has the cost: " << rst.first[i][j] << endl;
                    REQUIRE(rst.first[i][j] == expect[i][j]);
                    std::cout << "assertion passed" << endl;
                }
                std::cout << std::endl;
            }

        }
    }
}
