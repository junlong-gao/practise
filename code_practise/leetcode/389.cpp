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
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
class Solution {
public:
    char findTheDifference(string s, string t) {
        char hash[26];
        for(int i = 0; i < 26; ++i){
            hash[i] = 0;
        }
        for(int i = 0; i < s.size(); ++i){
            hash[s[i] - 'a'] ++;
        }
        for(int i = 0; i < t.size(); ++i){
            hash[t[i] - 'a'] --;
            if(hash[t[i] - 'a'] < 0) return t[i];
        }
        assert(0);
    }
};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


