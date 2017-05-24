#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <limits>
#include "catch.hpp"
#include "printer.h"

namespace lee54{
	using namespace std;
	class Solution {
        void helper(vector<int>& sofar, vector<vector<int>>& m, int i, int j){
            int r = m[i].size() - j;
            int d = m.size() - i;
            if(r - 1 < j || d - 1 < i) return;
            if(r - 1 == j && d - 1 == i){
                sofar.push_back(m[i][j]);
                return;
            }
            if(r - 1 == j){
                for(int k = i; k < d; ++k){
                    sofar.push_back(m[k][r-1]);
                }
                return;
            }
            if(d - 1 == i){
                for(int k = j; k < r; ++k){
                    sofar.push_back(m[i][k]);
                }
                return;
            }
            for(int k = j; k < r - 1; ++k){
                sofar.push_back(m[i][k]);
            }
            for(int k = i; k < d - 1; ++k){
                sofar.push_back(m[k][r-1]);
            }
            for(int k = r - 1; k > j; --k){
                sofar.push_back(m[d-1][k]);
            }
            for(int k = d - 1; k > i; --k){
                sofar.push_back(m[k][j]);
            }
            helper(sofar, m, i+1, j+1);
        }
	public:
        vector<int> spiralOrder(vector<vector<int>>& matrix) {
            vector<int> ret;
            helper(ret, matrix, 0, 0);
            return ret;
        }
	};


	TEST_CASE("smoke 54"){
		Solution testObj;
		SECTION("sample 0"){
            vector<vector<int>> testcase({{1,2,3},{8,9,4},{7,6,5}});
            vector<int> expected = {1,2,3,4,5,6,7,8,9};
            auto rst = testObj.spiralOrder(testcase);
            for(int i = 0; i < expected.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
		}
		SECTION("sample 1"){
            vector<vector<int>> testcase({{1,2},{4,3}});
            vector<int> expected = {1,2,3,4};
            auto rst = testObj.spiralOrder(testcase);
            for(int i = 0; i < expected.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
		}
		SECTION("sample 2"){
            vector<vector<int>> testcase({{1,2}});
            vector<int> expected = {1,2};
            auto rst = testObj.spiralOrder(testcase);
            for(int i = 0; i < expected.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
		}
		SECTION("sample 3"){
            vector<vector<int>> testcase({{1}});
            vector<int> expected = {1};
            auto rst = testObj.spiralOrder(testcase);
            for(int i = 0; i < expected.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
		}
		SECTION("sample 3"){
            vector<vector<int>> testcase({{1},{2},{3}, {4}});
            vector<int> expected = {1,2,3,4};
            auto rst = testObj.spiralOrder(testcase);
            for(int i = 0; i < expected.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
		}
		SECTION("sample 4"){
            vector<vector<int>> testcase({{1,2,3,4}});
            vector<int> expected = {1,2,3,4};
            auto rst = testObj.spiralOrder(testcase);
            for(int i = 0; i < expected.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
		}
	}
}
