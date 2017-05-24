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
        int jump(vector<int>& nums) {
            if(nums.size() == 1) return 0;
            int prevBoundary = nums[0];
            int curBoundary = nums[0];
            int step = 1;
            for(int i = 1; i < nums.size(); ++i){
                curBoundary = max(curBoundary, nums[i] + i);
                if(i == nums.size() - 1) return step;
                if(i == prevBoundary){
                    step ++;
                    prevBoundary = curBoundary;
                }
            }
            return step;
        }
    };
    
    TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){

		}
	}
}


