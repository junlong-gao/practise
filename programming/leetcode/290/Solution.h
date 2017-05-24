#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "catch.hpp"

namespace{
    using namespace std;
    class Solution_290 {
    public:
        bool wordPattern(string pattern, string str) {
            unordered_map<char, string> mapped;
            unordered_set<string> found;
            vector<string> strs;

            istringstream ss(str);
            string cur;
            while(ss>>cur){
                strs.push_back(cur);
            }
            if(strs.size()!=pattern.size())return false;
            auto s = strs.begin();

            for(auto c : pattern){
                string& cur = *s;
                auto it = mapped.find(c);
                if(it == mapped.end()){
                    auto ele = found.find(cur);
                    if(ele == found.end()){
                        found.insert(cur);
                        mapped.insert(make_pair(c, cur));
                    }else{
                        return false;
                    }
                }else{
                    if(it->second != cur) return false;
                }
                ++s;
            }
            return true;
        }
    };

    TEST_CASE( "test suite for 290", "[290]" ) {
        Solution_290 testObj;
        SECTION("smoke test"){
            string pattern = "abba";

            string str = "dog cat car dog";
            REQUIRE(testObj.wordPattern(pattern, str) == false);

            str = "dog cat cat dog";
            REQUIRE(testObj.wordPattern(pattern, str) == true);
        }
    }
}
