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
        bool verifyPreorder(vector<int>& preorder) {
            vector<int> s, ordered;
            for(int i = 0; i < preorder.size(); ++i){
                if(ordered.size() > 0 && ordered.back() > preorder[i]) return false;
                while(!s.empty() && s.back() < preorder[i]){
                    ordered.push_back(s.back()), s.pop_back();
                }
                s.push_back(preorder[i]);
            }
            return true;
        }
        
    };

	TEST_CASE("tests"){
		Solution testObj;
        SECTION("corner"){
            vector<int> testcase{2, 1};
            REQUIRE(testObj.verifyPreorder(testcase));
        }
        SECTION("corner"){
            vector<int> testcase{1, 2};
            REQUIRE(testObj.verifyPreorder(testcase));
        }
		SECTION("sample"){
            vector<int> testcase{1, -1, 2};
            REQUIRE(testObj.verifyPreorder(testcase));
		}
        SECTION("sample"){
            vector<int> testcase{10, 5, 1, 6, 15, 12, 17};
            REQUIRE(testObj.verifyPreorder(testcase));
        }
        SECTION("WA1"){
            vector<int> testcase{2,3,1};
            REQUIRE(!testObj.verifyPreorder(testcase));
        }
	}
}


