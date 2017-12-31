#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>


namespace lee275{
    using namespace std;
	class Solution {
	public:
		int hIndex(vector<int>& citations) {
            int i = 0, j = citations.size();
            int n = citations.size();
            while(i < j){
                int mid = i + (j - i)/2;
                int h = n - mid;
                if(h > citations[mid]){
                    i = mid + 1;
                }
                if(h < citations[mid]){
                    j = mid;
                }
                if(h == citations[mid]){
                    return citations[mid];
                }
            }
            return n - j; //this is tricky
		}
	};
	TEST_CASE("lee275 smoke"){
        Solution testObj;
        SECTION("sample"){
            vector<int> testcase{0,0,1,1,2,2,3};
            REQUIRE(testObj.hIndex(testcase) == 2);
        }
        SECTION("sample"){
            vector<int> testcase{0,1,1,1};
            REQUIRE(testObj.hIndex(testcase) == 1);
        }
        SECTION("sample"){
            vector<int> testcase{0,1,1,2};
            REQUIRE(testObj.hIndex(testcase) == 1);
        }
        SECTION("corner"){
            vector<int> testcase{0};
            REQUIRE(testObj.hIndex(testcase) == 0);
        }
        SECTION("corner"){
            vector<int> testcase{1};
            REQUIRE(testObj.hIndex(testcase) == 1);
        }
        SECTION("corner"){
            vector<int> testcase{2};
            REQUIRE(testObj.hIndex(testcase) == 1);
        }
        SECTION("sample 4"){
            vector<int> testcase{4, 4, 4, 4};
            REQUIRE(testObj.hIndex(testcase) == 4);
        }
	}
}


