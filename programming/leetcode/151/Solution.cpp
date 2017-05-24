#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>


namespace{
	using namespace std;
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
	class Solution {
	public:
		void reverseWords(string &s) {
            if(s.empty()) return;
            int i = 0;
            while(i < (int)s.length() && s[i] == ' ') ++i;
            s = s.substr(i, s.length() - i);
            while(s.size() > 0 && s.back() == ' ') s.pop_back();
            i = 0;
            while( i < (int)s.length()){
                if(s[i] == ' '){
                    int j = i + 1;
                    while(j < (int)s.length() && s[j] == ' '){
                        j++;
                    }
                    s.erase(i+1, j - i - 1);
                }
                i++;
            }
			for(int i = 0; i < (int)s.length() - i - 1; ++i){
				swap(s[i], s[s.length() - i - 1]);
			}
            i = 0;
			while(i < s.length()){
				int j = i + 1;
				while(j < s.length() && s[j]!=' '){j++;}
				for(int k = 0; k < (j - i) - k - 1; ++k){
					swap(s[k + i], s[(j - i) - k  - 1 + i]);
				}
				i = j + 1;
			}
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
			string s = "sky is blueeeee";
			string expected = "blueeeee is sky";
			testObj.reverseWords(s);
			REQUIRE(s == expected);
		}
        SECTION("sample"){
            string s = " a    b  cccc cc ";
            string expected = "cc cccc b a";
            testObj.reverseWords(s);
            REQUIRE(s == expected);
        }
	}
}


