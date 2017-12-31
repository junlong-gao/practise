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
		int largestRectangleArea(vector<int>& heights) {
			heights.push_back(0);
			vector<int> s;
			s.push_back(-1);
			int cur_max = 0;
			for(int i = 0; i < heights.size(); ++i){
				while(s.back() != -1 && heights[i] <= heights[s.back()]){
					int top = s.back(); s.pop_back();
					cur_max = max(cur_max, heights[top] * (i - s.back() - 1));
				}
				s.push_back(i);
			}
			return cur_max;
		}
	};

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
			vector<int> heights = {1,2,0,1};
			REQUIRE(testObj.largestRectangleArea(heights) == 2);

		}
	}
}


