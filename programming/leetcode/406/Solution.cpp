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
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(), people.end(), [&](const pair<int, int>& l, const pair<int, int>& r){
           if(l.first != r.first) return l.first < r.first; 
           return l.second > r.second;
        });
        vector<pair<int, int>> rst;
        while(!people.empty()){
            auto person = people.back();
            people.pop_back();
            rst.insert(rst.begin() + person.second, person);
        }
        return rst;
    }
};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
			vector<pair<int,int>> testcase{{1,2}, {7,0}, {6, 1}}, expected{{7,0}, {6,1},{1,2}};
            auto rst = testObj.reconstructQueue(testcase);
            REQUIRE(rst.size() == expected.size());
            for(int i = 0; i < expected.size(); ++i){
                REQUIRE(rst[i] == expected[i]);
            }
		}
	}
}


