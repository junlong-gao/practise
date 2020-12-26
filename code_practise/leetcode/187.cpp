#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;

	class Solution {
    public:
        vector<string> findRepeatedDnaSequences(string s) {
            unordered_set<string> table;
            unordered_set<string> out;
            for(int i = 0; i + 10 - 1 < s.length(); ++i){
                string t = s.substr(i, 10);
                if(table.find(t) != table.end()){
                    out.insert(t);
                }else{
                    table.insert(t);
                }
            }
            return vector<string>(out.begin(), out.end());
        }
    };

    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


