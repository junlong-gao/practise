#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <limits>
#include "catch.hpp"
#include "printer.h"

namespace lee391{
	using namespace std;
    class Solution {
    public:
        bool isRectangleCover(vector<vector<int>>& rectangles) {
            unordered_map<int, unordered_set<int>> incomming;
            unordered_map<int, unordered_set<int>> leaving;
            unordered_set<int> tmp;
            for(int i = 0; i < rectangles.size(); ++i){
                incomming[rectangles[i][0]].insert(i);
                leaving[rectangles[i][2]].insert(i);
                tmp.insert(rectangles[i][0]);
                tmp.insert(rectangles[i][2]);
            }
            vector<int> xaxis(tmp.begin(), tmp.end());
            sort(xaxis.begin(), xaxis.end());
            auto comp = [&](const int& lhs, const int& rhs) -> bool {
                if(rectangles[lhs][1] != rectangles[rhs][1])
                    return rectangles[lhs][1] < rectangles[rhs][1];
                if(rectangles[lhs][3] != rectangles[rhs][3])
                    return rectangles[lhs][3] < rectangles[rhs][3];
                return lhs < rhs;
            };
            set<int, decltype(comp)> cur(comp);
            pair<int, int> p;
            for(int i = 0; i < xaxis.size() - 1; ++i){
                int x = xaxis[i];
                for(auto& idx: leaving[x]){
                    cur.erase(idx);
                }
                for(auto& idx : incomming[x]){
                    auto it = cur.lower_bound(idx);
                    if(it != cur.end()){
                        if(rectangles[idx][3] > rectangles[*it][1]) return false;
                    }
                    if(it!= cur.begin()){
                        auto pre = prev(it);
                        if(rectangles[idx][1] < rectangles[*pre][3]) return false;
                    }
                    cur.insert(idx);
                }
                if(cur.size() == 0) return false;
                auto rst = make_pair(rectangles[*cur.begin()][1], rectangles[*cur.rbegin()][3]);
                if(i != 0 && (rst.first != p.first || rst.second != p.second)){
                        return false;
                }else{
                    p = rst;
                }
            }
            return true;
        }
    };


	TEST_CASE("smoke 391"){
		Solution testObj;

		SECTION("sample 0"){
            auto testcase = vector<vector<int>>({{1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}});
			REQUIRE(testObj.isRectangleCover(testcase));
		}

        SECTION("sample 1"){
            auto testcase = vector<vector<int>>({{1,1,2,3},{1,3,2,4},{3,1,4,2},{3,2,4,4}});
            REQUIRE(!testObj.isRectangleCover(testcase));
        }
        SECTION("sample 2"){
            auto testcase = vector<vector<int>>({{1,1,3,3},{3,1,4,2},{1,3,2,4},{2,2,4,4}});
            REQUIRE(!testObj.isRectangleCover(testcase));
        }

        SECTION("sample 3"){
            auto testcase = vector<vector<int>>({{1,1,3,3},{1,1,3,3}});
            REQUIRE(!testObj.isRectangleCover(testcase));
        }
	}
}
