#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <limits>
#include "catch.hpp"
#include "printer.h"

namespace{
	using namespace std;
	class Solution {
        void helper(vector<vector<int>>& m, int n, int i, int j){
            int r = m[i].size() - j;
            int d = m.size() - i;
            if(r - 1 < j || d - 1 < i) return;
            if(r - 1 == j && d - 1 == i){
                m[i][j] = n++;
                return;
            }
            if(r - 1 == j){
                for(int k = i; k < d; ++k){
                    m[k][r-1] = n++;
                }
                return;
            }
            if(d - 1 == i){
                for(int k = j; k < r; ++k){
                    m[i][k] = n++;
                }
                return;
            }
            for(int k = j; k < r - 1; ++k){
                m[i][k] = n++;
            }
            for(int k = i; k < d - 1; ++k){
                m[k][r-1] = n++;
            }
            for(int k = r - 1; k > j; --k){
                m[d-1][k] = n++;
            }
            for(int k = d - 1; k > i; --k){
                m[k][j] = n++;
            }
            helper(m, n, i + 1, j + 1);
        }
	public:
        vector<vector<int>> generateMatrix(int n) {
            vector<vector<int>> ret(n, vector<int>(n, 0));
            helper(ret, 1, 0, 0);
            return ret;
        }
	};


	TEST_CASE("smoke 59 "){
		Solution testObj;
		SECTION("sample 2"){
            vector<vector<int>> expected({{1}});
            auto rst = testObj.generateMatrix(1);
            for(int i = 0; i < rst.size(); ++i){
                for(int j = 0; j <rst[i].size(); ++j){
                    REQUIRE(rst[i][j] == expected[i][j]);
                }
            }
		}
		SECTION("sample 1"){
            vector<vector<int>> expected({{1,2},{4,3}});
            auto rst = testObj.generateMatrix(2);
            for(int i = 0; i < rst.size(); ++i){
                for(int j = 0; j <rst[i].size(); ++j){
                    REQUIRE(rst[i][j] == expected[i][j]);
                }
            }
		}
		SECTION("sample 0"){
            vector<vector<int>> expected({{1,2,3},{8,9,4},{7,6,5}});
            auto rst = testObj.generateMatrix(3);
            for(int i = 0; i < rst.size(); ++i){
                for(int j = 0; j <rst[i].size(); ++j){
                    REQUIRE(rst[i][j] == expected[i][j]);
                }
            }
		}
    }
}
