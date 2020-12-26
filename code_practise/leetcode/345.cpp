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
        string reverseVowels(string s) {
            unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u',
                'A','E','I','O','U',
            };
            int i = 0, j = s.length() - 1;
            while(true){
                while(vowels.find(s[i]) == vowels.end()) ++i;
                if(i >= j) break;
                while(vowels.find(s[j]) == vowels.end()) --j;
                if(i >= j) break;
                swap(s[i],s[j]);
                i++;j--;
                
            }
            return s;
        }
    };

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


