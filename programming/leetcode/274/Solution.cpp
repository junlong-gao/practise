#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>


namespace lee274{
    using namespace std;
	class Solution {
	public:
		int hIndex(vector<int>& citations) {
			vector<int> table(citations.size()+1, 0);
			int n = citations.size();
			for(int i = 0; i < n; ++i){
				table[min(citations[i], n)] ++;
			}
			int tmp = 0;
			for(int h = n; h >= 0; --h){
				if(tmp <= h && (tmp+=table[h]) >= h){
					return h;
				}
			}
			return 0;
		}
	};
	TEST_CASE("lee274 smoke"){
        Solution testObj;
        SECTION("sample"){
            vector<int> testcase{3, 0, 5, 6,1,2};
            REQUIRE(testObj.hIndex(testcase) == 3);
        }
        SECTION("corner"){
            vector<int> testcase{0};
            REQUIRE(testObj.hIndex(testcase) == 0);
        }
        SECTION("corner"){
            vector<int> testcase{1};
            REQUIRE(testObj.hIndex(testcase) == 1);
        }
	}
}


