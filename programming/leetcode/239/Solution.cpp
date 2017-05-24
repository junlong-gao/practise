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
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
            vector<int> rst;
            deque<int> window;
            for(int i = 0; i < nums.size(); ++i){
                
                if(!window.empty() && window.back() < i - k + 1){
                    window.pop_back();
                }
                
                while(!window.empty() && nums[window.front()] <= nums[i]){
                    window.pop_front();
                }
                window.push_front(i);
                if(i >= k - 1){
                    rst.push_back(nums[window.back()]);
                }
            }
            return rst;
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            vector<int> expected{3, 3,5,5,6,7};
            vector<int> testcases{1,3,-1,-3,5,3,6,7};
            auto rst = testObj.maxSlidingWindow(testcases, 3);
            for(int i = 0; i < expected.size(); ++i){
                REQUIRE(expected[i] == rst[i]);
            }
		}
	}
}


