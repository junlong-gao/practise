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
        string minWindow(string s, string t) {
            unordered_map<char, int> copy, table;
            for(int i = 0; i < t.length(); ++i){
                copy[t[i]]++;
            }
            table = copy;
            int i = 0, j = 0;
            int tofind = t.length();
            int cur = numeric_limits<int>::max();
            string ans = "";
            while(i < s.length()){
                while(tofind > 0 && j < s.length()){
                    if(copy.find(s[j]) != copy.end()){
                        //cout << "increase j" << endl;
                        if(copy[s[j]]>0) tofind--;
                        copy[s[j]]--;
                        //cout << s[j] << " " << copy[s[j]] << endl;
                        
                    }
                    ++j;
                }
                while(tofind == 0 && i < s.length()){
                    if(copy.find(s[i]) != copy.end()){
                        if(copy[s[i]] != table[s[i]]){
                            //cout << "increase i" << endl;
                            copy[s[i]]++;
                            //cout << s[i] << " " << copy[s[i]] << endl;
                            if(copy[s[i]] == 1){
                                if(j - i < cur){
                                    //cout << s[i] << " " << i << " " << j << endl;
                                    cur = j - i;
                                    ans = s.substr(i, j - i);
                                }
                                tofind++;
                            }
                        }
                    }
                    ++i;
                }
                if(j == s.length()) break;
            }
            return ans;
        }
    };
    
    TEST_CASE("tests"){
        Solution testObj;
        SECTION("sample"){
            REQUIRE(testObj.minWindow("aababa", "abb")=="bab");
		}
	}
}


