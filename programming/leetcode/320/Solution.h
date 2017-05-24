#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <limits>
#include "catch.hpp"
#include "printer.h"

namespace lee320{
	using namespace std;
	class Solution {
		vector<string> bucket;
		void helper(string so_far, string& word, int pos){
			if(pos >= word.length()){
				bucket.push_back(so_far);
			}else{
				helper(so_far + word[pos], word, pos + 1);
				for(int i = pos + 1; i < word.length(); ++i){
					helper(so_far + to_string(i - pos) + word[i], word, i + 1);
				}
				helper(so_far + to_string(word.length() - pos), word, word.length() + 1);
			}
			
		}
	public:
		vector<string> generateAbbreviations(string word) {
			helper("", word, 0);
			return bucket;
		}
	};


	TEST_CASE("smoke 320"){
		Solution testObj;
		SECTION("sample 0"){
			vector<string> rst = testObj.generateAbbreviations("word");
			LOG(INFO) << sequential::printer(rst, [&](const string& e){
				return e;
			});
			REQUIRE(rst.size() == 16);
		}
	}
}
