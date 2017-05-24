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
        int minPatches(vector<int>& nums, int n) {
            long cur = 0;
            int count = 0;
            for(int i = 0; i < nums.size(); ++i){
                while(cur < n && cur < nums[i] - 1){
                    count ++;
                    cur = cur*2 + 1;
                }
                cur += nums[i];
            }
            while(cur < n){
                count++;
                cur = cur*2 + 1;
            }
            return count;
        }
    };

	TEST_CASE("tests"){
		Solution testObj;
		SECTION("sample"){
            vector<int> test = {1,7,21,31,34,37,40,43,49,87,90,92,93,98,99};
            REQUIRE(testObj.minPatches(test, 12) == 2);
		}
	}
}


