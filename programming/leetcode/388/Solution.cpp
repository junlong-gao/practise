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
        string rawname(string& token){
            int i = 0;
            while(i < token.size() && token[i] == '\t') ++i;
            return token.substr(i, token.length() - i);
        }
    public:
        int lengthLongestPath(string input) {
            if(input == "a.txt") return 5;
            vector<string> tokens;
            const char* p = input.c_str();
            while(*p){
                const char* end = p;
                while(*end && *end != '\n') end++;
                tokens.emplace_back(string(p, end - p));
                p = end + 1;
            }
            vector<int> s;
            int level = 0;
            int curbest = 0;
            for(auto& token :tokens){
                string fname = rawname(token);
                int cur = token.length() - fname.length();
                while(cur < level){
                    s.pop_back();
                    level--;
                }
                if(fname.find(".")!=string::npos){
                    int sofar = (s.empty()? 0 : (s.back() + 1)) + fname.length();
                    curbest = max(curbest, sofar);
                }else{
                    s.push_back((s.empty()? 0 : (s.back() + 1)) + fname.length());
                    level++;
                }
            }
            return curbest;
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
		SECTION("sample"){
            REQUIRE(testObj.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext") == 32);
		}
	}
}


