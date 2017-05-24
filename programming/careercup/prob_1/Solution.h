#include <string>
#include <unordered_map>
#include "catch.hpp"

namespace prob_1{
	using namespace std;
	bool has_anagram(string src, string target){
		unordered_map<char, int> bucket;
		if(target.length() < src.length()) return false;
		for(auto c : src){
			bucket[c] += 1;
		}
		int i = 0, j = 0;
		while(j < target.size()){
			while(j < target.size() && 
					j - i < src.length()){
				bucket[target[j]] -= 1;
				if(bucket[target[j]] == 0){
					bucket.erase(target[j]);
				}
				j++;
			}
			if(bucket.empty()) return true;
			while(j - i >= src.length()){
				bucket[target[i]] += 1;
				if(bucket[target[i]] == 0){
					bucket.erase(target[i]);
				}
				i++;
			}
		}
		return false;	
	}
	TEST_CASE("has anagram smoke"){
		REQUIRE(has_anagram("a","b") == false);
		REQUIRE(has_anagram("xyz","afdzxyksl") == true);
		REQUIRE(has_anagram("xyz","afdzyksl") == false);
	}
}
